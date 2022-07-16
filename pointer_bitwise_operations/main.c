#include <stdio.h>

#define LEN_INT 4

void print_bytes(int num); // prints all bytes of the number
int swap_bytes(int num, int n, int m); // swaps the n-th and m-th byte

int main() {
    int num = 0xABCDEFBB;
    print_bytes(num);
    printf("\n");
    num = swap_bytes(num, 1, 3);
    print_bytes(num);
    return 0;
}
void print_bytes(int num) {
    char* byte_num = (char*)&num;
    for(int i = 0; i < LEN_INT; i++) {
        printf("%d byte is %X\n", i, byte_num[i]&0xFF);
    }
}
int swap_bytes(int num, int n, int m) {
    // check correct arguments
    char* byte_num = (char*)&num;
    n = ((n >= 0) && (n < LEN_INT))*n + (n >= LEN_INT)*3;
    m = ((m >= 0) && (m < LEN_INT))*m + (m >= LEN_INT)*3;
    int byte_n = byte_num[n];
    int byte_m = byte_num[m];
    byte_num[n] = byte_m;
    byte_num[m] = byte_n;
    return num;
}
