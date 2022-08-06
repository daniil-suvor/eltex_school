#include "calculator.h"
void difference() {
    int minuend, subtrahend;
    printf("Input two integer arguments\n");
    if (scanf("%d %d", &minuend, &subtrahend) == 2){
        printf("result is %d\n", minuend - subtrahend);
    } else {
        printf("Error arguments!\n");
    }
}
