#ifndef TELEFONE_DIRECTORY_H_
#define TELEFONE_DIRECTORY_H_

/*  
    module define interface for work with phone directory 
    
    init_directory - function initialization empty telephone directory.
    Return a pointer to a new structure and NULL otherwise.
    
    delete_contact - function delete contact.
    Function use telephone number for find needing contact.
    Function return 1 if delete was success and 0 otherwise.

    find_contact - function for find contact.
    Function use telephone number for find needing contact.
    Function return struct contact* if find was success and NULL otherwise.

    add_contact - function for add contact.
    Function return 1 if add was success and 0 otherwise.
    Сontacts are added in ascending order of phone number.

    free_telephone_directory - function for free memory for all contacts.
*/

#define MAX_NAME 51    // max length of contact name or last name

enum COMAND {
    ADD,
    DELETE,
    FIND,
    OUTPUT_CONTACTS,
    EXIT
};
struct contact {
    struct contact* next;
    struct contact* previous;
    char name[MAX_NAME];
    char lastname[MAX_NAME];
    int phone_number;
};

struct contact* init_directory(int number, char* name, char* lastname);
int delete_contact(struct contact** direcotry, int number);
struct contact* find_contact(struct contact* direcotry, int number);
int add_contact(struct contact** direcotry, int number, char* name, char* lastname);
void free_telephone_directory(struct contact* head_direcotry);
#endif  // TELEFONE_DIRECTORY_H_