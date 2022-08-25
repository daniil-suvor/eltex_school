#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>


int main() {
    if (mkfifo("fd_chaild", S_IRWXU) != 0) {
        fprintf(stderr, "ERROR\n");
        exit(0);
    }
    int fd_chaild = open("fd_chaild", O_RDWR);
    if (fd_chaild == -1) {
        fprintf(stderr, "ERROR 1\n");
        exit(0);
    }
    int fd_perent = open("fd_chaild", O_RDWR);
    if (fd_perent == -1) {
        fprintf(stderr, "ERROR 2\n");
        exit(0);
    }
    pid_t pid = fork();
    if (pid == 0) {
        char str[20];
        write(fd_chaild, "from c child!\n", 15);
        printf("pid child is %d\n", pid);
        exit(0);
    } else {
        char str[20];
        read(fd_chaild, str, 20);
        wait(0);
        printf("%s", str);
        printf("pid perent is %d\n", pid);
    }
    close(fd_chaild);
    close(fd_perent);
    remove("fd_chaild");
    exit(0);
}