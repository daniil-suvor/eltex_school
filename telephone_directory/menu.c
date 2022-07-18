#include <stdio.h>
#include "telephone_directory.h"
#include "menu.h"

int main() {
    menu();
    return 0;
}
void menu_delete(struct telephone_directory* directory) {
    int number = 0;
    printf("Input phone number for delete\n");
    if (scanf("%d", &number) == 1) {
        if (delete_contact(directory, number) == 1) {
            printf("Contact isn't finded!\n\n");
        }
    } else {
        free_buff();
        printf("Not correct phone number!\n\n");
    }
}
void menu_find(struct telephone_directory* directory) {
    int number = 0;
    struct contact* f_contact;
    printf("Input phone number for find\n");
    if (scanf("%d", &number) == 1) {
        f_contact = find_contact(directory, number);
        if (f_contact != NULL) {
            printf("Find contact:\n");
            print_contact(f_contact);
        } else {
            printf("Contact isn't finded!\n\n");
        }
    } else {
        free_buff();
        printf("Not correct phone number!\n\n");
    }
}
void print_contact(struct contact* contact) {
    printf("Name is %s\n", contact->name);
    printf("Lastname is %s\n", contact->lastname);
    printf("Phone number is %d\n\n", contact->phone_number);
}
void print_all_contact(struct telephone_directory* direcotry) {
     for (int i = 0; i < MAX_NUMBER; i++) {
        if (direcotry->contacts[i].phone_number != -1) {
            print_contact(&direcotry->contacts[i]);
        }
    }
}
void print_menu() {
    printf("Input comands:\n");
    printf("0 - for add contacts\n");
    printf("1 - for delete contact\n");
    printf("2 - for find contact\n");
    printf("3 - for output all contats\n");
    printf("4 - for exit\n");
}
void menu() {
    struct telephone_directory directory;
    init_directory(&directory);
    int comand = 0;
    while (comand != EXIT) {
        print_menu();
        printf("\033[H\033[J");
        if (scanf("%d", &comand) != 1) {
            printf("Error comand!\n");
            free_buff();
        };
        switch(comand) {
            case(ADD):
                add_contact(&directory);
                break;
            case(DELETE):
                menu_delete(&directory);
                break;
            case(FIND):
                menu_find(&directory);
                break;
            case(OUTPUT_CONTACTS):
                print_all_contact(&directory);
                break;
            case(EXIT):
                break;
            default:
                printf("Error comand!\n");
                free_buff();
                break;
        }
    }
}
