#include <pthread.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h> 

#define THREAD 4
#define NUM_SHOPS 5

FILE* shop_log = NULL;
int need[THREAD - 1];
struct shop {
    int products;
    pthread_mutex_t satus;
} shops[NUM_SHOPS];

void* loader() {
    int i = 0;
    while (need[0] != 0 || need[1] != 0 || need[2] != 0) {
        // i = rand() % NUM_SHOPS;
        i++;
        i %= NUM_SHOPS;
        if (pthread_mutex_trylock(&shops[i].satus) == 0) {
        //pthread_mutex_lock(&shops[i].satus);
            fprintf(shop_log, "loader: shop %d before %d after %d\n", i, shops[i].products, shops[i].products + 500);
            shops[i].products += 500;
            pthread_mutex_unlock(&shops[i].satus);
            sleep(1);
        }
    }
    return 0;
}
void* buyer(void* args) {
    int* arg = (int*)args;
    int i = 0; 
    while (*arg != 0) {
        // i = rand() % NUM_SHOPS;
        i++;
        i %= NUM_SHOPS;
        if (pthread_mutex_trylock(&shops[i].satus) == 0) {
        //pthread_mutex_lock(&shops[i].satus);
            if (shops[i].products >= *arg) {
                fprintf(shop_log, "buyer: shop %d btfore %d after %d\n", i, shops[i].products, shops[i].products - *arg);
                shops[i].products -= *arg;
                *arg = 0;
            } else {
                fprintf(shop_log, "buyer: shop %d btfore %d after %d\n", i, shops[i].products, 0);
                (*arg) -= shops[i].products;
                shops[i].products = 0;
            }
            pthread_mutex_unlock(&shops[i].satus);
            sleep(2);
        }
    }
    return 0;
}
int main() {
    shop_log = fopen("log", "w");
    if (shop_log == NULL) {
        fprintf(stderr, "System Error!\n");
        exit(0);
    }
    srand(time(NULL));
    // pthread_mutexattr_t attr;
    // pthread_mutexattr_init(&attr);
    // pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_ERRORCHECK);
    for (int i = 0 ; i < NUM_SHOPS; i++) {
        shops[i].products = 900 + (rand() % 201);
        fprintf(shop_log, "shop %d have %d products\n", i, shops[i].products);
        // pthread_mutex_init(&shops[i].satus, &attr);
        shops[i].satus = (pthread_mutex_t)PTHREAD_MUTEX_INITIALIZER;
    }
    pthread_t tid[THREAD];
    for (int i = 0; i < THREAD - 1; i++) {
        need[i] = 9500 + (rand() % 1001);
        pthread_create(&tid[i], NULL, buyer, (void*)&need[i]);
    }
    pthread_create(&tid[THREAD - 1], NULL, loader, NULL);
    for (int i = 0; i < THREAD; i++) {
        pthread_join(tid[i], NULL);
    }
    fprintf(shop_log, "all everyone bought everything :)");
    fclose(shop_log);
    return 0;
}