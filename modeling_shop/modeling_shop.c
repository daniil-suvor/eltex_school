#include <pthread.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h> 

/*
    simulation of buyers in stores. 
    buyer - a thread that randomly goes shopping and buys everything until he has zero need.
    loader - a thread that randomly goes shopping and delivers 500 products.
*/

#define THREAD 4
#define NUM_SHOPS 5
#define SLEEP_BUYER 2
#define SLEEP_LOADER 1

FILE* shop_log = NULL;
int need[THREAD - 1];
struct shop {
    int products;
    pthread_mutex_t status;
} shops[NUM_SHOPS];

void* loader() {
    int i = 0;
    while (need[0] != 0 || need[1] != 0 || need[2] != 0) {
        i = rand() % NUM_SHOPS;  // for random chose shop, so as not to try to enter the shop one after another
        if (pthread_mutex_trylock(&shops[i].status) == 0) {
            fprintf(shop_log, "loader: shop %d before %d after %d\n", i, shops[i].products, shops[i].products + 500);
            shops[i].products += 500;
            pthread_mutex_unlock(&shops[i].status);
            sleep(SLEEP_LOADER);
        }
    }
    exit(0);
}
void* buyer(void* args) {
    int* arg = (int*)args;
    int i = 0; 
    while (*arg != 0) {
        i = rand() % NUM_SHOPS;  // for random chose shop, so as not to try to enter the shop one after another
        if (pthread_mutex_trylock(&shops[i].status) == 0) {
            if (shops[i].products >= *arg) {
                fprintf(shop_log, "buyer: shop %d btfore %d after %d\n", i, shops[i].products, shops[i].products - *arg);
                shops[i].products -= *arg;
                *arg = 0;
            } else {
                fprintf(shop_log, "buyer: shop %d btfore %d after %d\n", i, shops[i].products, 0);
                (*arg) -= shops[i].products;
                shops[i].products = 0;
            }
            pthread_mutex_unlock(&shops[i].status);
            sleep(SLEEP_BUYER);
        }
    }
    exit(0);
}
int main() {
    shop_log = fopen("log", "w");  // create log file
    if (shop_log == NULL) {        // check file create
        fprintf(stderr, "System Error!\n");
        exit(0);
    }
    srand(time(NULL));             // for random
    // pthread_mutexattr_t attr;
    // pthread_mutexattr_init(&attr);
    // pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_ERRORCHECK);
    for (int i = 0 ; i < NUM_SHOPS; i++) {    // create mutex for each shop, and random generate products
        shops[i].products = 900 + (rand() % 201);
        fprintf(shop_log, "shop %d have %d products\n", i, shops[i].products);
        // pthread_mutex_init(&shops[i].status, &attr);
        shops[i].status = (pthread_mutex_t)PTHREAD_MUTEX_INITIALIZER;
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