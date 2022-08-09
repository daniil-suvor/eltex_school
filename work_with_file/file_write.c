#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <stdio.h>


int main() {
    char file_name[20] = "example.txt";
    int fd = open(file_name, O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR);
    if (fd != -1) {
        char str[20] = "Hello World!";
        write(fd, str, strlen(str));
        close(fd);
    } else {
        fprintf(stderr,"Error open!\n");
    }
    return 0;
}