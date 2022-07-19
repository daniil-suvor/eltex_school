#ifndef MENU_H_
#define MENU_H_
void print_menu();
void menu();
void menu_find(struct telephone_directory* directory);
void menu_delete(struct telephone_directory* directory);
void print_contact(struct contact* contact);
void print_all_contact(struct telephone_directory* direcotry);
void free_buff();
#endif  // MENU_H_