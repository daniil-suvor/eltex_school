#include <stdio.h>

#define LEN_BYT 4

void print_bytes(int num);
int main() {
    int num = 0xABCDEFBB;
    print_bytes(num);
    return 0;
}
void print_bytes(int num) {
    for(int i = 0; i < LEN_BYT; i++) {
        printf("%d byte is %X\n", (i + 1), (num & 0xFF)); // print last byte
        num = num >> 8; // shift one byte to the left
    }
}
