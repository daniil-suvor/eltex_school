#include <string.h>
#include <malloc.h>
#include "telephone_directory.h"

struct contact* init_directory(int number, char* name, char* lastname) {
    struct contact* head_directory = (struct contact*)calloc(1, sizeof(struct contact));
    if (head_directory != NULL) {
        head_directory->next = NULL;
        head_directory->previous = NULL;
        strcpy(head_directory->name, name);
        strcpy(head_directory->lastname, lastname);
        head_directory->phone_number = number;
    }
    return head_directory;
}
int delete_contact(struct contact** head_direcotry, int number) {
    int rez = 0;
    struct contact* buff_head = NULL;
    if ((*head_direcotry)->phone_number == number) {
        buff_head = *head_direcotry;
        *head_direcotry = (*head_direcotry)->next;
        free(buff_head);
        rez = 1;
    } else {
        buff_head = *head_direcotry;
        while ((buff_head != NULL) && (buff_head-> phone_number > number)) {
            buff_head = buff_head->next;
        }
        if ((buff_head != NULL) && (buff_head->phone_number == number)) {
            buff_head->previous->next = buff_head->next;
            buff_head->next->previous = buff_head->previous;
            free(buff_head);
            rez = 1;
        }
    }
    return rez;
}
struct contact* find_contact(struct contact* head_direcotry, int number) {
    while ((head_direcotry != NULL) && (head_direcotry->phone_number < number)) {
        head_direcotry = head_direcotry->next;
    }
    if ((head_direcotry != NULL) && (head_direcotry->phone_number == number)) {
        return head_direcotry;
    } else {
        return NULL;
    }
}
int add_contact(struct contact** head_direcotry, int number, char* name, char* lastname) {
    int rez = 0;
    struct contact* buff_head = NULL;
    struct contact* new_contact = init_directory(number, name, lastname);
    if (new_contact != NULL) {
        if ((*head_direcotry)->phone_number > number) {
            new_contact->next = (*head_direcotry);
            (*head_direcotry)->previous = new_contact;
            *head_direcotry = new_contact;
            rez = 1;
        } else {
            buff_head = *head_direcotry;
            while ((buff_head->next != NULL) && (buff_head->next->phone_number <= number)) {
                buff_head = buff_head->next;
            }
            new_contact->next = buff_head->next;
            new_contact->previous = buff_head;
            buff_head->next = new_contact;
            rez = 1;
        }
    }
    return rez;
}
void free_telephone_directory(struct contact* head_direcotry) {
    if (head_direcotry != NULL) {
        struct contact* buff = head_direcotry->next;
        free(head_direcotry);
        free_telephone_directory(buff);
    }
}
