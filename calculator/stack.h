#ifndef _STACK_H_
#define _STACK_H_
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
