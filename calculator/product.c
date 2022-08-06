#include "calculator.h"
void product() {
    int fractor1, fractor2;
    printf("Input two integer arguments\n");
    if (scanf("%d %d", &fractor1, &fractor2) == 2){
        printf("result is %d\n", fractor1*fractor2);
    } else {
        printf("Error arguments!\n");
    }
}
