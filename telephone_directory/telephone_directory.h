#ifndef TELEFONE_DIRECTORY_H_
#define TELEFONE_DIRECTORY_H_

/*  
    module define interface for work with phone directory 
    
    init_directory - function initialization empty telephone directory.
    Function give telephone number values -1, it is flag of empty contact
    
    delete_contact - function delete contact.
    Function use telephone number for find needing contact.
    Function return 0 if delete was success and 1 otherwise.

    find_contact - function for find contact.
    Function use telephone number for find needing contact.
    Function return struct contact* if find was success and NULL otherwise.

    add_contact - function for add contact.
    Function return 0 if add was success and 1 otherwise.
*/

#define MAX_NUMBER 10  // max count contact in telephone directory
#define MAX_NAME 51    // max length of contact name or last name

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
    struct contact contacts[MAX_NUMBER];  // list of contacts
    int amount;  // amount contacts
};

void init_directory(struct telephone_directory* direcotry);
int delete_contact(struct telephone_directory* direcotry, int number);
struct contact* find_contact(struct telephone_directory* direcotry, int number);
int add_contact(struct telephone_directory* direcotry, struct contact* contact);
#endif  // TELEFONE_DIRECTORY_H_