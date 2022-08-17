#ifndef _MY_VIM_H_
#define _MY_VIM_H_

#include <termios.h>
#include <sys/ioctl.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <curses.h>

#define MAX_LEN 128

struct node {
    struct node* next;
    struct node* prev;
    char str[MAX_LEN + 1];
    int len;
};
struct node* init(char* str, int len);
struct node* add(struct node* elem, char* str, int len);
struct node* delete_elem(struct node* elem);
void free_node(struct node* head);

void sig_winch();
struct node* read_file(FILE* fd, int* str_num, int col);
void save_file(FILE* fd, struct node* head);
void reloand_window(struct node* head, int row);

#endif  // _MY_VIM_H_
