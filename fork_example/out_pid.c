#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

void print_pid(char* str) {
    printf("it is %s!\n", str);
    printf("PID is %d\n", getpid());
    printf("PPID is %d\n", getppid());
}
int main() {
    pid_t pid = fork();
    if (pid == 0) {
        print_pid("child");
        exit(0);
    } else {
        print_pid("perent");
        wait(0);
    }
    exit(0);
}
