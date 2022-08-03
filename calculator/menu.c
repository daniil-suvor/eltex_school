#include <stdio.h>
#include "calculator.h"
void check_scanf(int* a, int* b);
void print_menu();
void free_buff();
void menu();

int main() {
    menu();
    return 0;
}
void check_scanf(int* a, int* b) {
    printf("Input arguments\n");
    while (scanf("%d %d", a, b) != 2) {
        printf("Error input, try again!\n");
        free_buff();
    }
}
void print_menu() {
    printf("Menu of calculator\n");
    printf("Input comand:\n");
    printf("1 - for sum\n");
    printf("2 - for difference\n");
    printf("3 - for product\n");
    printf("4 - for fraction\n");
    printf("5 - for exit\n");
}
void free_buff() {
    char ch;
    while ((ch = getchar()) != '\n') {}
}
void menu() {
    int a, b, comand;
    while(comand != 5) {
        print_menu();
        if (scanf("%d", &comand) != 1) {
            free_buff();
            comand = 6;
        }
        switch(comand) {
            case 1:
                check_scanf(&a, &b);
                printf("rezult is %d\n", sum(a, b));
                break;
            case 2:
                check_scanf(&a, &b);
                printf("rezult is %d\n", difference(a, b));
                break;
            case 3:
                check_scanf(&a, &b);
                printf("rezult is %d\n", product(a, b));
                break;
            case 4:
                check_scanf(&a, &b);
                printf("rezult is %d\n", fraction(a, b));
                break;
            case 5:
                break;
            default:
                printf("Error comand!\n");
                break;
        }
    }
}