#include <stdio.h>
#include <dlfcn.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include "stack.h"

void print_menu();
void free_buff();
void menu();
void find_name(char* func_name, char* library);

int main() {
    menu();
    return 0;
}
void find_name(char* func_name, char* library) {
    for (int i = 3; library[i] != '.'; i++) {
        func_name[i - 3] = library[i];
    }
}
void print_menu() {
    printf("Menu of calculator\n");
    printf("Input comand:\n");
    printf("1 - for sum\n");
    printf("2 - for difference\n");
    printf("3 - for product\n");
    printf("4 - for fraction\n");
    printf("5 - for exit\n");
}
void free_buff() {
    char ch;
    while ((ch = getchar()) != '\n') {}
}
void menu() {
    void *library;	// хандлер внешней библиотеки
	void (*func)();	// переменная для хранения адреса функции

	//загрузка библиотеки
    DIR *folder;
    struct dirent *entry;
    folder = opendir("plagins/");
    if(folder == NULL) {
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
    func = (head->func);
    func();
    // int comand = 0;
    // while(comand != 5) {
    //     print_menu();
    //     if (scanf("%d", &comand) != 1) {
    //         free_buff();
    //         comand = 6;
    //     }
    //     switch(comand) {
    //         case 1:
    //             check_scanf(&a, &b);
    //             printf("rezult is %d\n", sum(a, b));
    //             break;
    //         case 2:
    //             check_scanf(&a, &b);
    //             printf("rezult is %d\n", difference(a, b));
    //             break;
    //         case 3:
    //             check_scanf(&a, &b);
    //             printf("rezult is %d\n", product(a, b));
    //             break;
    //         case 4:
    //             check_scanf(&a, &b);
    //             printf("rezult is %d\n", fraction(a, b));
    //             break;
    //         case 5:
    //             break;
    //         default:
    //             printf("Error comand!\n");
    //             break;
    //     }
    // }
    struct stack* buff = head;
    while (buff != NULL) {
        dlclose(buff->library);
        buff = buff->next;
    }
    free_stack(head);
}