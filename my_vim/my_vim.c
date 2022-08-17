#include "my_vim.h"

void sig_winch() {
    struct winsize size;
    ioctl(fileno(stdout), TIOCGWINSZ, (char *) &size);
    resizeterm(size.ws_row, size.ws_col);
}
struct node* read_file(FILE* fd, int* str_num, int col) {
    struct node* res = NULL;
    char str[MAX_LEN + 1];
    while (fgets(str, col, fd) != NULL) {
        res = add(res, str, (int)strlen(str));
        *str_num += 1;
    }
    if (res == NULL) {
        res = add(res, "", 0);
    } else {
        while (res->prev != NULL) {
            res = res->prev;
        }
    }
    return res;
}
void save_file(FILE* fd, struct node* head) {
    while (head->prev != NULL) {
        head = head->prev;
    }
    while (head != NULL) {
        fputs(head->str, fd);
        head = head->next;
    }
}
void reloand_window(struct node* head, int row) {
    int str_num = 0;
    while ((head != NULL) && (str_num < row)) {
        move(str_num, 0);
        printw(head->str);
        head = head->next;
        str_num++;
    }
}
int main(int argc, char* argv[]) {
    if (argc != 2) {    // check arguments number, need one argument - name of file
        fprintf(stderr, "Error arguments number!\n");
        exit(0);
    }
    FILE* fd = fopen(argv[1], "r+");
    if (fd == NULL) {
        fprintf(stderr, "%s - No such file or directory\n", argv[1]);
        exit(0);
    } 
    int str_num = 0;
    initscr();                    // output window initiation
    signal(SIGWINCH, sig_winch);  // change parametrs window size
    curs_set(TRUE);               // disable character output when typing
    keypad(stdscr, TRUE);         // special key processing
    noecho();
    refresh();
    move(0,0);
    int x = 0, y = 0, max_x = 0, max_y = 0;
    getmaxyx(stdscr, max_y, max_x);
    max_x = (max_x > MAX_LEN) ? MAX_LEN : max_x;
    struct node* str_file = read_file(fd, &str_num, max_x);  // initiating a linked list storing a string from a file
    reloand_window(str_file, max_y);    // output file to window 
    int ch;
    move(0, 0);
    while ((ch = getch()) != KEY_F(3)) {   // reading until F3 is pressed
        refresh();                         // reloand window
        switch (ch) {
            case KEY_UP:                   // move up to the head of the list (beginning of the file)
                if (str_file->prev != NULL) {
                    str_file = str_file->prev;
                    y--;
                    x = (x > str_file->len) ? str_file->len: x;
                }
                break;
            case KEY_DOWN:                 // move down to the end of the list (end of the file)
                if (str_file->next != NULL) {
                    str_file = str_file->next;
                    y++;
                    x = (x > str_file->len) ? str_file->len : x;
                }
                break;
            case KEY_LEFT:                 // move left
                x = x - (x > 0);
                break;
            case KEY_RIGHT:                // move right
                x = x + (x < (str_file->len));
                break;
            case '\n':                     // create new line
                str_file = add(str_file, str_file->str + x, str_file->len - x + (str_file->next != NULL));
                str_file->prev->str[x]= '\n';
                str_file->prev->str[x + 1] = '\0';
                str_file->prev->len = x;
                x = 0;
                clrtoeol();                // clean line from the cursor
                y++;
                move(y, 0);
                insdelln(1);              // add line above cursor
                printw(str_file->str);
                break;
            case KEY_BACKSPACE:           // delete symbol
                if (x > 0) {
                    x--;
                    memmove(str_file->str + x, str_file->str + x + 1,  str_file->len - x + (str_file->next != NULL));
                    str_file->len -= 1;
                    move(y, x);
                    delch();
                }
                break;
            case KEY_F(2):               // save file
                rewind(fd);
                fd = freopen(argv[1], "w", fd);
                if (fd != NULL) {
                    save_file(fd, str_file);
                } else {
                    fprintf(stderr, "Save error!\n");
                }
                break;
            default:
                if ((ch >= 0x20) && (ch < 0x7f)) {
                    if (str_file->len < max_x) {
                        insch(ch);
                        memmove(str_file->str + x + 1, str_file->str + x, str_file->len - x + (str_file->next != NULL));
                        (str_file->str)[x] = ch;
                        str_file->len += 1;
                        x++;
                    }
                }
                break;
        }
        move(y, x);
    }
    while (str_file->prev != NULL) {
        str_file = str_file->prev;
    }
    free_node(str_file);
    endwin();
    exit(0);
}
