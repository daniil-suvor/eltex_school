#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
    for (int i = 0; i < argc; i++) {
        printf("%2d is %s\n", i,  argv[i]);
    }
    exit(0);
}
