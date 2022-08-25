#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <dirent.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

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
    closedir(dir);
    return res;
}
int main() {
    char* comand[20];
    int word_num = -1, word_i = 0, dir_num = 0, pipefd_i = 0, pipefd[20][2];;
    char *dir_list[20];
    char ch = 'a', prev_ch = ' ';
    char* path = getenv("PATH");
    strcat(path, ":.");
    // add all directory with executable file to array dir_list
    char* dir = strtok(path, ":");
    while (dir != NULL) {
        dir_list[dir_num] = dir;
        dir_num++;
        dir = strtok(NULL, ":");
    }
    do {
        ch = getchar();
        switch (ch) {
            case '\n':
                if (word_num == -1) { // checl empty line
                    fprintf(stderr, "Syntaxis error!\n");
                    break;
                }
            case '|' :
                if (pipe(pipefd[pipefd_i]) != 0) {
                    fprintf(stderr, "pipe error!\n");
                    exit(0);
                }
                comand[word_num + 1] = NULL;
                for (int i = 0; i < dir_num; i++) {
                    if (find_file(comand[0], dir_list[i]) == 1) {
                        size_t end_dir = strlen(dir_list[i]);
                        strcat(dir_list[i], "/");
                        strcat(dir_list[i], comand[0]); // forming pathway to file
                        pid_t pid = fork();
                        if (pid == 0) {
                            // Redirect previous output channel to current input channel
                            if (pipefd_i > 0) {
                                if (dup2(pipefd[pipefd_i - 1][0], STDIN_FILENO) == -1) {
                                    fprintf(stderr, "dup2 error!\n");
                                    exit(0);
                                }
                            }
                            if (ch != '\n') {  // Don't redirict if it is last comand
                                if (dup2(pipefd[pipefd_i][1], STDOUT_FILENO) == -1) {
                                    fprintf(stderr, "dup2 error!\n");
                                    exit(0);
                                }
                            }                               
                            execv(dir_list[i], comand);
                        } else {
                            wait(0);
                            close(pipefd[pipefd_i][1]);  // Close curent output chanel for end signal next input chanel
                            if (pipefd_i > 0)
                                close(pipefd[pipefd_i - 1][0]);  // Close previous input chanel because we used its
                            pipefd_i++;
                            dir_list[i][end_dir] = '\0';
                            break;
                        }
                    }
                }
                for (int i = 0; i <= word_num; i++) {
                    free(comand[i]);
                }
                word_i = 0;
                word_num = -1;
                if (ch != '\n')
                    ch = ' ';  // signal for next comand for start write new comand
                break;
            case ' ':
                break;
            default:
                if (prev_ch == ' ') {  // Signal for write new comand 
                    word_i = 0;
                    word_num++;
                    comand[word_num] = (char*)calloc(256, sizeof(char));
                }
                comand[word_num][word_i] = ch;
                word_i++;
                break;
        }
        prev_ch = ch;
    } while(ch != '\n');
    close(pipefd[pipefd_i - 1][0]);  // close last input chanel because we were closing previous channels in cycle
    exit(0);
}
