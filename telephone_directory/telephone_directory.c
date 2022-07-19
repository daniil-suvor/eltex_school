#include <string.h>
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
int add_contact(struct telephone_directory* direcotry, struct contact* contact) {
    for (int i = 0; i < MAX_NUMBER; i++) {
        if (direcotry->contacts[i].phone_number == -1) {
            direcotry->contacts[i].phone_number = contact->phone_number;
            strcpy(direcotry->contacts[i].name, contact->name);
            strcpy(direcotry->contacts[i].lastname, contact->lastname);
            direcotry->amount += 1;
            return 0;
        }
    }
    return 1;
}