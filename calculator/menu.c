#include <stdio.h>
#include <dlfcn.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include "stack.h"

#define MAX_LEM_FILE_NAME 256  // max length file name in Linux + \0

void print_menu(struct stack* head);
void free_buff();
void menu();
void get_func_name(char* func_name, char* library);
struct stack* init_plagins();
void call_func(struct stack* head, int* comand);
void close_lib(struct stack* head);

int main() {
    menu();
    return 0;
}
void menu() {
    struct stack* head = init_plagins();
    int comand = 0;
    while(comand != -1) {
        print_menu(head);
        call_func(head, &comand);
        putchar('\n');
    }
}
struct stack* init_plagins() {
    void *library = NULL;    // pointer to dynamic library
	void (*func)() = NULL;   // pointer to function to dynamic library
    DIR *folder;             // pointer to structure for read directory
    struct dirent *entry;    // pointer to file in directiry
    folder = opendir("plagins/"); // open directiry
    if (folder == NULL) {         // check open directiry
        perror("Unable to read directory");
        exit(0);
    }
    struct stack* head = init(-1, "exit", func, library); // init first element to stack
    int number = 0;
    char func_name[MAX_LEM_FILE_NAME];
    char* error;
    while ((entry=readdir(folder)) != NULL) {
        char plagins_adr[MAX_LEM_FILE_NAME + 10] = "plagins/";   // way to directory with plagins +10 it is length "plagins"
        library = dlopen(strcat(plagins_adr, entry->d_name), RTLD_LAZY);  // read library
        if (library != NULL) {
            get_func_name(func_name, entry->d_name);   // get name of function
            func = dlsym(library, func_name);          // get pointer to function
            if ((error = dlerror()) == NULL)  {
                head = add(head, number, func_name, func, library);
                number++;
            }
        }
    }
    closedir(folder);
    return head;
}
void print_menu(struct stack* head) {
    printf("Menu of calculator\n");
    printf("Input comand:\n");
    while (head != NULL) {
        printf("%3d - for %s\n", head->number, head->name_func);
        head = head->next;
    }
}
// function name is lib<function name>.so
void get_func_name(char* func_name, char* library) {
    int i = 3;
    for (i = 3; library[i] != '.'; i++) {
        func_name[i - 3] = library[i];
    }
    func_name[i - 3] = '\0';
}
void free_buff() {
    char ch;
    while ((ch = getchar()) != '\n') {}
}
void call_func(struct stack* head, int* comand) {
    void (*func)();
    if ((scanf("%d", comand) == 1) && (*comand <= head->number) && (*comand >= 0)) {
        while ((head != NULL) && (head->number != *comand)) {
            head = head->next;
        }
        func = (head->func);
        func();
    } else if (*comand == -1) {
        close_lib(head);
    } else {
        printf("Error comand!\n");
        free_buff();
    }
}
void close_lib(struct stack* head) {
    struct stack* buff = head;
    while (buff->next != NULL) {  // dont close last library because last elemet (close) don't have pointer to library
        dlclose(buff->library); // close dinamyc library
        buff = buff->next;
    }
    free_stack(head);
}
