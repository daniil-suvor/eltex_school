#include <stdio.h>

#define LEN_ARR 9

void init_arr(int* arr);
void reverse_arr(int* arr);
void print_arr(int* arr);

int main() {
    int arr[LEN_ARR];
    init_arr(arr);
    print_arr(arr);
    reverse_arr(arr);
    print_arr(arr);
}
void init_arr(int* arr) {
    for(int i = 0; i < LEN_ARR; i++) {
        arr[i] = i + 1;
    }
}
void reverse_arr(int* arr) {
    int buff = 0;
    for(int i = 0; i < LEN_ARR/2; i++) {
        buff = arr[i];
        arr[i] = arr[LEN_ARR - i - 1];
        arr[LEN_ARR - i - 1] = buff;
    }
}
void print_arr(int* arr) {
    for(int i = 0; i < LEN_ARR; i++) {
        printf("%d ", arr[i]);
    }
    putchar('\n');
}