#include "calculator.h"
void fraction() {
    int dividend, divisor;
    printf("Input two integer arguments\n");
    if ((scanf("%d %d", &dividend, &divisor) == 2) && (divisor != 0)){
        printf("result is %d\n", dividend / divisor);
    } else {
        printf("Error arguments!\n");
    }
}
