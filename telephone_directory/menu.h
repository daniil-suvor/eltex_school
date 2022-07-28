#ifndef MENU_H_
#define MENU_H_

/*
    Module define menu functions for work with telephone directory.
    Module use interfaces of telephone directory.

    print_menu - function draw out text commands for telephone directory to strdout.

    menu - function initialization new telephone directory.
    Function parse command for telephone directory.

    menu_find, menu_delete, menu_add_contat - functions use
    relevant interfaces telephone directory and process errors.
    Function print all contact with need number.
    
    print_contact - function draw out all fields structure contact
    
    print_all_contact - function draw out all contats 
    
    free_buff - function clear input buffer.
    Clear input buffer if previous input has errors or input was bigger than max length name.
*/

void print_menu();
void menu();
void menu_find(struct contact* directory);
void menu_delete(struct contact** directory);
void menu_add_contact(struct contact** directory);
void print_contact(struct contact* contact);
void print_all_contact(struct contact* direcotry);
void free_buff();
#endif  // MENU_H_