#include "calculator.h"
void sum() {
    int addend1, addend2;
    printf("Input two integer arguments\n");
    if (scanf("%d %d", &addend1, &addend2) == 2){
        printf("result is %d\n", addend1 + addend2);
    } else {
        printf("Error arguments!\n");
    }
}
