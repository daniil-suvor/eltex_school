#include <stdio.h>

#define LEN_BYT 8
#define LEN_INT 4

void print_bytes(int num);
int get_byte(int num, int n);
int insert_byte(int num, int n, int ins_byte);

int main() {
    int num = 0xABCDEFBB;
    print_bytes(num);
    printf("\n");
    int c = get_byte(num, 2);
    num = insert_byte(num, 3, c);
    print_bytes(num);
    return 0;
}
void print_bytes(int num) {
    for(int i = 0; i < LEN_INT; i++) {
        printf("%d byte is %X\n", i, (num & 0xFF)); // print last byte
        num = num >> LEN_BYT; // shift one byte to the left
    }
}
int get_byte(int num, int n) {
    return (num >> LEN_BYT*n) & 0xFF;
}
int insert_byte(int num, int n, int ins_byte) {
    ins_byte = ins_byte << n*LEN_BYT;
    switch(n) {
        case 0:
            num = num & 0xFFFFFF00; break;
        case 1:
            num = num & 0xFFFF00FF; break;
        case 2:
            num = num & 0xFF00FFFF; break;
        case 3:
            num = num & 0x00FFFFFF; break;
    }
    num = num | ins_byte;
    return num;
}
