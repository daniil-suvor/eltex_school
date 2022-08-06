#include <malloc.h>
#include <string.h>
#include "stack.h"
struct stack* init(int number, char* func_name, void (*func), void *library) {
    struct stack* head = calloc(1, sizeof(struct stack));
    if (head != NULL) {
        head->name_func = calloc(strlen(func_name) + 1, sizeof(char));
        if (head->name_func != NULL) {
            strcpy(head->name_func, func_name);
            head->number = number;
            head->func = func;
            head->next = NULL;
            head->library = library;
        } else {
            free(head);
        }
    }
    return head;
}
struct stack* add(struct stack* head, int number, char* func_name, void (*func), void *library) {
    struct stack* new_head = init(number, func_name, func, library);
    if (new_head != NULL) {
        new_head->next = head;
        return new_head;
    } else {
        return head;
    }
}
void free_stack(struct stack* head) {
    if (head != NULL) {
        struct stack* buff = head->next;
        free(head->name_func);
        free(head);
        free_stack(buff);
    }
}