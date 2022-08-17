#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <dirent.h>
#include <stdlib.h>


int find_file(char* file_name, char* dir_name) {
    int res = 0;
    DIR *dir;
    struct dirent *file;
    dir = opendir(dir_name);
    if (dir != NULL) {
        while ((file = readdir(dir)) != NULL) {
            if ((file->d_type != 4) && (strcmp(file_name, file->d_name) == 0)) {
                res = 1;
                break;
            }
        }
    }
    return res;
}
int main(int argc, char* argv[]) {
    if (argc < 2) {
        exit(0);
    }
    char* path = getenv("PATH");
    strcat(path, ":.");
    char* dir = strtok(path, ":");
    while (dir != NULL) {
        if (find_file(argv[1], dir) == 1) {
            strcat(dir, "/");
            strcat(dir, argv[1]);
            if (execv(dir, argv + 1) != -1) {
                break;
            }
        }
        dir = strtok(NULL, ":");
    }
    exit(0);
}
    