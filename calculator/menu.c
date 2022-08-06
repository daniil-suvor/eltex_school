#include <stdio.h>
#include <dlfcn.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include "stack.h"

void print_menu(struct stack* head);
void free_buff();
void menu();
void find_name(char* func_name, char* library);
struct stack* init_plagins();

int main() {
    menu();
    return 0;
}
void find_name(char* func_name, char* library) {
    for (int i = 3; library[i] != '.'; i++) {
        func_name[i - 3] = library[i];
    }
}
void print_menu(struct stack* head) {
    printf("Menu of calculator\n");
    printf("Input comand:\n");
    while (head != NULL) {
        printf("%d - for %s\n", head->number, head->name_func);
        head = head->next;
    }
    printf("-1 - for exit\n");
}
void free_buff() {
    char ch;
    while ((ch = getchar()) != '\n') {}
}
void menu() {
    void (*func)();
    struct stack* head = init_plagins();
    int comand = 0;
    struct stack* buff;
    while(comand != -1) {
        print_menu(head);
        if ((scanf("%d", &comand) == 1) && (comand <= head->number) && (comand >= 0)) {
            buff = head;
            while ((buff != NULL) && (buff->number != comand)) {
                buff = buff->next;
            }
            func = (buff->func);
            func();
        } else if (comand != -1) {
            printf("Error comand!\n\n");
            free_buff();
        }
    }
    buff = head;
    while (buff != NULL) {
        dlclose(buff->library);
        buff = buff->next;
    }
    free_stack(head);
}
struct stack* init_plagins() {
    void *library;
	void (*func)();
    DIR *folder;
    struct dirent *entry;
    folder = opendir("plagins/");
    if (folder == NULL) {
        perror("Unable to read directory");
        exit(0);
    }
    int number = 0;
    char* func_name;
    struct stack* head = NULL;
    while( (entry=readdir(folder))) {
        char n[50] = "plagins/";
        library = dlopen(strcat(n, entry->d_name), RTLD_LAZY);
        if (library != NULL) {
            func_name = calloc(strlen(entry->d_name) + 1, sizeof(char));
            if (func_name == NULL)
                exit(0);
            find_name(func_name, entry->d_name);
            func = dlsym(library, func_name);
            if (head == NULL) {
                head = init(number, func_name, func, library);
            } else {
                head = add(head, number, func_name, func, library);
            }
            number++;
            free(func_name);
        }
    }
    closedir(folder);
    return head;
}