#include "chat_room.h"
#include <pthread.h>
#include <termios.h>
#include <sys/ioctl.h>
#include <signal.h>
#include <curses.h>

WINDOW* list_wind, *list_subwind, *wind, *subwind;
pthread_spinlock_t lock;
void sig_winch() {
    struct winsize size;
    ioctl(fileno(stdout), TIOCGWINSZ, (char *) &size);
    resizeterm(size.ws_row, size.ws_col);
}
void* listener(void* arg) {
    int max_y, max_x;
    getmaxyx(stdscr, max_y, max_x);
    max_y++;
    struct message message;
    mqd_t client = *(mqd_t*)arg;
    int y = 0, new_line;
    while (1) {
        if (mq_receive(client, (char*)&message, sizeof(struct message), NULL) != -1) {
            new_line = (strlen(message.mes) / (max_x - 2)) + 2;
            pthread_spin_lock(&lock);
                wmove(list_subwind, y, 0);
                y += new_line;
                waddstr(list_subwind, message.from + 1);
                waddstr(list_subwind, message.mes);
                wrefresh(list_subwind);
            pthread_spin_unlock(&lock);
        }
        if (pthread_setcancelstate(PTHREAD_CANCEL_DISABLE, NULL) != 0) {
            break;
        }
    }
    return NULL;
}
void* sender(void* arg) {
    struct message message;
    struct client* info = (struct client*)arg;
    mqd_t server = info->id;
    strcpy(message.from, info->name);
    while (1) {
        wrefresh(wind);
        pthread_spin_lock(&lock);
            wmove(subwind, 0, 0);
            wclear(subwind);
        pthread_spin_unlock(&lock);
        wgetnstr(subwind, message.mes, MAX_MES_LEN);
        if (strcmp(message.mes, ":exit") == 0) {
            message.type = 1;
            mq_send(server, (char*)&message, sizeof(struct message), 0);
            break;
        } else if (message.mes[0] != '\0') {
            message.type = 2;
            if (mq_send(server, (char*)&message, sizeof(struct message), 0) == -1) {
                fprintf(stderr, "Erorr send message to server\n");
            }
        }
    }
    return NULL;
}
int main() {
    struct mq_attr attr;
    attr.mq_flags = 0;
    attr.mq_maxmsg = MAX_LEN_QUEUE;
    attr.mq_msgsize = sizeof(struct message);
    attr.mq_curmsgs = 0;
    mqd_t client, server;
    if ((server = mq_open(SERVER_NAME, O_RDWR)) == -1) {
        fprintf(stderr, "Server is not available\n");
        exit(0);
    }
    char name[MAX_NAME_LEN + 2];
    printf("Input name, max length name is %d\n", MAX_NAME_LEN);
    name[0] = '/';
    fgets(name + 1, MAX_NAME_LEN, stdin);
    if ((client = mq_open(name, O_RDWR | O_CREAT | O_NONBLOCK, QUEUE_PERMISSIONS, &attr)) == -1) {
        fprintf(stderr, "Erorr open server\n");
        exit(0);
    }
    struct message mes;
    strcpy(mes.from, name);
    mes.type = 0;
    if (mq_send(server, (char*)&mes, sizeof(struct message), 0) == -1) {
        fprintf(stderr, "Erorr send message to server\n");
    } else {
        initscr();
        signal(SIGWINCH, sig_winch);
        
        int max_y, max_x;
        getmaxyx(stdscr, max_y, max_x);
        list_wind = newwin(max_y - 5, max_x, 1, 1); 
        box(list_wind, 0, 0);
        list_subwind = derwin(list_wind, max_y - 7, max_x - 2, 1, 1);
        wind = newwin(5, max_x, max_y - 4, 0);
        box(wind, 0, 0);
        subwind = derwin(wind, 3, max_x - 2, 1, 1);
        nodelay(list_wind, TRUE);
        wrefresh(list_wind);
        wrefresh(wind);
        refresh();

        pthread_spin_init(&lock, PTHREAD_PROCESS_PRIVATE);
        pthread_t tid_listeber, tid_sender;
        pthread_create(&tid_listeber, NULL, listener, (void*)&client);
        struct client for_sender;
        strcpy(for_sender.name, name);
        for_sender.id = server;
        pthread_create(&tid_sender, NULL, sender, (void*)&for_sender);
        pthread_join(tid_sender, NULL);
        pthread_cancel(tid_listeber);
        delwin(list_wind);
        delwin(list_subwind);
        delwin(wind);
        delwin(subwind);
        endwin();
        pthread_spin_destroy(&lock);
    }
    mq_close(client);
    mq_unlink(name);
    return 0;
}