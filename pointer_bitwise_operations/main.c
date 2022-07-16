#include <stdio.h>

void print_bytes(void* num, int len_num); // prints all bytes of the number
void swap_bytes(void* num, int n, int m, int len_num); // swaps the n-th and m-th byte

int main() {
    int num = 0xABCDEFBB;
    print_bytes(&num, sizeof(num));
    printf("\n");
    swap_bytes(&num, 1, 3, sizeof(num));
    print_bytes(&num, sizeof(num));
    double num1 = 14563.2156231;
    printf("--------------------------------------------------------------\n");
    print_bytes(&num1, sizeof(num1));
    printf("\n");
    swap_bytes(&num1, 0, 6, sizeof(num1));
    print_bytes(&num1, sizeof(num1));
    printf("--------------------------------------------------------------\n");
    char str[20] = "Hello world!";
    print_bytes(str, sizeof(str));
    printf("\n");
    swap_bytes(str, 0, 6, sizeof(str));
    print_bytes(str, sizeof(str));
    return 0;
}
void print_bytes(void* num, int len_num) {
    char* byte_num = (char*)num;
    for(int i = 0; i < len_num; i++) {
        printf("%3d byte is %X\n", i, byte_num[i]&0xFF);
    }
}
void swap_bytes(void* num, int n, int m, int len_num) {
    // check correct arguments
    char* byte_num = (char*)num;
    n = ((n >= 0) && (n < len_num))*n + (n >= len_num)*3;
    m = ((m >= 0) && (m < len_num))*m + (m >= len_num)*3;
    int byte_n = byte_num[n];
    int byte_m = byte_num[m];
    byte_num[n] = byte_m;
    byte_num[m] = byte_n;
}
