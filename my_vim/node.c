#include "my_vim.h"

// void change_str_num(struct node* head, int change) {
//     while (head != NULL) {
//         head->str_num += change;
//         head = head->next;
//     }
// }
struct node* init(char* str, int len) {
    struct node* head = (struct node*)calloc(1, sizeof(struct node));
    if (head != NULL) {
        head->len = len - (str[len - 1] == '\n');
        strncpy(head->str, str, len);
        head->next = NULL;
        head->prev = NULL;
    }
    return head;
}
struct node* add(struct node* elem, char* str, int len) {
    struct node* new_elem = init(str, len);
    if (new_elem != NULL) {
        if (elem == NULL) {
            elem = new_elem;
        } else {
            new_elem->next = elem->next;    
            new_elem->prev = elem;
            elem->next = new_elem;
            if (new_elem->next != NULL) {
                new_elem->next->prev = new_elem;
            }
            elem = elem->next;
        }
    }
    return elem;
}
struct node* delete_elem(struct node* elem) {
    if (elem != NULL) {
        struct node* free_buf = elem;
        elem = elem->next;
        if (elem != NULL) {
            elem->prev = free_buf->prev;
            if (elem->prev != NULL) {
                elem->prev->next = elem;
            }
        }
        free(free_buf);
    }
    return elem;
}
void free_node(struct node* head) {
    if (head != NULL) {
        struct node* next_buf = head->next;
        free(head);
        free_node(next_buf);
    }
}
