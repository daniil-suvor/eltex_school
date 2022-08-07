#include "calculator.h"

void logorifm() {
    double argument;
    printf("Input one argument\n");
    if (scanf("%lf", &argument) == 1){
        printf("result is %lf\n", log(argument));
    } else {
        printf("Error argument!\n");
    }
}
