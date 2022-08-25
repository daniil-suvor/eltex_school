#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    int pipefd_chaild[2];
    int pipefd_perent[2];
    pipe(pipefd_chaild);
    pipe(pipefd_perent);
    pid_t pid = fork();
    if (pid == 0) {
        char str[20];
        write(pipefd_chaild[1], "from child!\n", 13);
        read(pipefd_perent[0], str, 20);
        printf("%s", str);
        printf("%d\n", pid);
        exit(0);
    } else {
        char str[20];
        write(pipefd_perent[1], "from perent!\n", 14);
        read(pipefd_chaild[0], str, 20);
        printf("%s", str);
        printf("%d\n", pid);
        wait(0);
    }
    exit(0);
}