#include <pthread.h>
#include <stdio.h>

void* sum_a(void* a) {
    int* b = (int*)a;
    for (int i = 0; i < 1000000; i++) {
        (*b)++;
    }
    return 0;
}
int main() {
    int a = 0;
    void* status;
    pthread_t tid[5];
    for (int i = 0; i <5; i++) {
        pthread_create(&tid[i], NULL, sum_a, (void*)&a);
    }
    for (int i = 0; i < 5; i++) {
        pthread_join(tid[i], &status);
    }
    printf("%d\n", a);
    return 0;
}