#include <stdio.h>
#include "telephone_directory.h"

void init_directory(struct telephone_directory* direcotry) {
    for (int i = 0; i < MAX_NUMBER; i++) {
        direcotry->contacts[i].phone_number = -1;
    }
    direcotry->amount = 0;
}
int delete_contact(struct telephone_directory* direcotry, int number) {
    for (int i = 0; i < MAX_NUMBER; i++) {
        if (direcotry->contacts[i].phone_number == number) {
            direcotry->contacts[i].phone_number = -1;
            direcotry->amount -= 1;
            return 0;
        }
    }
    return 1;
}
struct contact* find_contact(struct telephone_directory* direcotry, int number) {
    for (int i = 0; i < MAX_NUMBER; i++) {
        if (direcotry->contacts[i].phone_number == number) {
            return &direcotry->contacts[i];
        }
    }
    return NULL;
}
void free_buff() {
    char ch;
    while ((ch = getchar()) != '\n') {}
}
int add_contact(struct telephone_directory* direcotry) {
    for (int i = 0; i < MAX_NUMBER; i++) {
        if (direcotry->contacts[i].phone_number == -1) {
            printf("input name\n");
            scanf("%50s", (direcotry->contacts[i].name));
            free_buff();
            printf("input lastname\n");
            scanf("%50s", direcotry->contacts[i].lastname);
            free_buff();
            printf("input phone number\n");
            while(scanf("%d", &direcotry->contacts[i].phone_number) != 1) {
                printf("Error number, try again!\n");
                free_buff();
            }
            direcotry->amount += 1;
            return 0;
        }
    }
    return 1;
}
