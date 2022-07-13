#include <stdio.h>

#define SIZE_MATR 7

void init_matr(int (*matr)[SIZE_MATR]);
void print_matr(int (*matr)[SIZE_MATR]);

int main() {
    int matr[SIZE_MATR][SIZE_MATR];
    init_matr(matr);
    print_matr(matr);
    return 0;
}
void init_matr(int (*matr)[SIZE_MATR]) {
    for(int i = 0; i < SIZE_MATR; i++) {
        for(int j =0; j < SIZE_MATR; j++) {
            matr[i][j] = 1 + j +i*SIZE_MATR;
        }
    }
}
void print_matr(int (*matr)[SIZE_MATR]) {
    for(int i = 0; i < SIZE_MATR; i++) {
        for(int j =0; j < SIZE_MATR; j++) {
            printf("%4d ", matr[i][j]);
        }
        putchar('\n');
    }
}