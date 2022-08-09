#include <unistd.h>
#include <fcntl.h>
#include <malloc.h>
#include <string.h>
#include <stdio.h>

int main() {
    char file_name[20] = "example.txt";
    int fd = open(file_name, O_RDWR);
    if (fd != -1) {
        long len = lseek(fd, 0, SEEK_END);
        char buf[2];
        while (len > 0) {
            len--;
            lseek(fd, len, SEEK_SET);
            read(fd, buf, 1);
            putchar(buf[0]);
        }
        putchar('\n');
        close(fd);
    } else {
        fprintf(stderr,"Error open %s!\n", file_name);
    }
    return 0;
}