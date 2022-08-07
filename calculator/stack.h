#ifndef _STACK_H_
#define _STACK_H_
/*
    stack module for storing functions and open dynamic libraries.
    implementation stack on linked list.
    init - function to initialize a new stack element
    add - function to add new element to head, return new head
    free_stack - function to free allocated memory
*/
struct stack {
    struct stack* next;
    void *library;
    int number;
    char* name_func;
    void (*func);
};
struct stack* init(int number, char* func_name, void (*func), void *library);
struct stack* add(struct stack* head, int number, char* func_name, void (*func), void *library);
void free_stack(struct stack* head);
#endif  // _STACK_H_
