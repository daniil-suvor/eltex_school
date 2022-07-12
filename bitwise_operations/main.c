#include <stdio.h>

#define LEN_BYT 8
#define LEN_INT 4

void print_bytes(int num); // prints all bytes of the number
int get_byte(int num, int n); // gets n-th byte
int insert_byte(int num, int n, int ins_byte); // inserts a byte in n-th place
int swap_bytes(int num, int n, int m); // swaps the n-th and m-th byte

int main() {
    int num = 0xABCDEFBB;
    print_bytes(num);
    printf("\n");
    num = swap_bytes(num, 3, 1);
    print_bytes(num);
    return 0;
}
void print_bytes(int num) {
    for(int i = 0; i < LEN_INT; i++) {
        printf("%d byte is %X\n", i, (num & 0xFF)); // print last byte
        num = num >> LEN_BYT; // shift one byte to the right
    }
}
int get_byte(int num, int n) {
    return (num >> LEN_BYT*n) & 0xFF;
}
int insert_byte(int num, int n, int ins_byte) {
    ins_byte = ins_byte << n*LEN_BYT;  // shift n-th byte to the left
    switch(n) { // delete a byte in n-th place
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
int swap_bytes(int num, int n, int m) {
    // check correct arguments
    n = ((n >= 0) && (n < LEN_INT))*n + (n >= LEN_INT)*3;
    m = ((m >= 0) && (m < LEN_INT))*m + (m >= LEN_INT)*3;
    int byte_n = get_byte(num, n);
    int byte_m = get_byte(num, m);
    num = insert_byte(num, m, byte_n);
    num = insert_byte(num, n, byte_m);
    return num;
}
