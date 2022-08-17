#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main() {
    execl("./example", "first", "second", "third", NULL);
    exit(0);
}
