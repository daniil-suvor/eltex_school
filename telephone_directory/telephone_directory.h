#ifndef TELEFONE_DIRECTORY_H_
#define TELEFONE_DIRECTORY_H_

#define MAX_NUMBER 10
#define MAX_NAME 51

enum COMAND {
    ADD,
    DELETE,
    FIND,
    OUTPUT_CONTACTS,
    EXIT
};
struct contact {
    char name[MAX_NAME];
    char lastname[MAX_NAME];
    int phone_number;
};
struct telephone_directory {
    struct contact contacts[MAX_NUMBER];
    int amount;
};

void init_directory(struct telephone_directory* direcotry);
int delete_contact(struct telephone_directory* direcotry, int number);
struct contact* find_contact(struct telephone_directory* direcotry, int number);
int add_contact(struct telephone_directory* direcotry, struct contact* contact);
void free_buff();
#endif  // TELEFONE_DIRECTORY_H_