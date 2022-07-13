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
    int str = 0;
    int col = 0;
    int num = 1;
    for(int i = 0; i < SIZE_MATR; i++) {
        for(int j = 0; j < SIZE_MATR; j++) {
            matr[i][j] = 0;
        }
    }
    while(num < SIZE_MATR*SIZE_MATR) {
        while((col < SIZE_MATR - 1) && (matr[str][col + 1] == 0)) {
            matr[str][col] = num;
            col++;
            num++;
        }
        while((str < SIZE_MATR - 1) && (matr[str + 1][col] == 0)) {
            matr[str][col] = num;
            str++;
            num++;
        }
        while((col > 0) && (matr[str][col - 1] == 0)) {
            matr[str][col] = num;
            col--;
            num++;
        }
        while((str > 0) && (matr[str - 1][col] == 0)) {
            matr[str][col] = num;
            str--;
            num++;
        }
    }
    matr[str][col] = SIZE_MATR*SIZE_MATR;
}
void print_matr(int (*matr)[SIZE_MATR]) {
    for(int i = 0; i < SIZE_MATR; i++) {
        for(int j =0; j < SIZE_MATR; j++) {
            printf("%4d ", matr[i][j]);
        }
        putchar('\n');
    }
}