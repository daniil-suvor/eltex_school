#include <stdio.h>
#include "telephone_directory.h"
#include "menu.h"

int main() {
    menu();
    return 0;
}
void menu_delete(struct contact** directory) {
    int number = 0;
    printf("Input phone number for delete\n");
    if (scanf("%d", &number) == 1) {
        if (*directory != NULL) {
            if (delete_contact(directory, number) == 0) {
                printf("Contact isn't finded!\n\n");
            } else {
                printf("Success delete!\n\n");
            }
        } else {
            printf("Error delete. directory is empty!\n\n");
        }
    } else {
        printf("Not correct phone number!\n\n");
    }
}
void menu_find(struct contact* directory) {
    int number = 0;
    struct contact* f_contact;
    printf("Input phone number for find\n");
    if (scanf("%d", &number) == 1) {
        f_contact = find_contact(directory, number);
        if (f_contact != NULL) {
            while((f_contact != NULL) && (f_contact->phone_number == number)) {
                printf("Find contact:\n");
                print_contact(f_contact);
                f_contact = f_contact->next;
            }
        } else {
            printf("Contact isn't finded!\n\n");
        }
    } else {
        printf("Not correct phone number!\n\n");
    }
}
void print_contact(struct contact* contact) {
    printf("Name is %s\n", contact->name);
    printf("Lastname is %s\n", contact->lastname);
    printf("Phone number is %d\n\n", contact->phone_number);
}
void print_all_contact(struct contact* direcotry) {
    while (direcotry != NULL) {
        print_contact(direcotry);
        direcotry = direcotry->next;
    }
}
void menu_add_contact(struct contact** directory) {
    int number = 0;
    char name[MAX_NAME];
    char lastname[MAX_NAME];
    printf("input name\n");
    scanf("%50s", name);
    free_buff();  //Clear input buffer if input was bigger than max length name.
    printf("input lastname\n");
    scanf("%50s", lastname);
    free_buff();  // Clear input buffer if input was bigger than max length name.
    printf("input phone number\n");
    while((scanf("%d", &number) != 1) || (number < 0)) { 
        printf("Error number, try again!\n");
        free_buff();  // Clear input buffer if previous input has errors
    }
    if (*directory != NULL) {
        if (add_contact(directory, number, name, lastname) == 0) {
            printf("Failed to add new contact\n");
        }
    }else {
        *directory = init_directory(number, name, lastname);
    }
}
void free_buff() {
    char ch;
    while ((ch = getchar()) != '\n') {}
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
    struct contact* directory = NULL;
    int comand = 0;
    while (comand != EXIT) {
        //printf("\033[H\033[J");  // clear screen
        print_menu();
        scanf("%d", &comand);
        switch(comand) {
            case(ADD):
                menu_add_contact(&directory);
                break;
            case(DELETE):
                menu_delete(&directory);
                break;
            case(FIND):
                menu_find(directory);
                break;
            case(OUTPUT_CONTACTS):
                print_all_contact(directory);
                break;
            case(EXIT):
                break;
            default:
                printf("Error comand!\n");
                break;
        }
        free_buff();
    }
    free_telephone_directory(directory);
}
