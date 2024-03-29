#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "mutex.h"

pthread_t *phil;
mutex_t *baguette;
int PHILOSOPHES;

void mange(int id) {}

void* philosophe(void* arg)
{
    int id=  *((int *) arg);
    int left = id;
    int right = (left + 1) % PHILOSOPHES;
    for (int i = 0 ; i<10000 ; i++) {
        // philosophe pense

        if(left<right) {
            mutex_lock(&baguette[left]);
            mutex_lock(&baguette[right]);
        }
        else {
            mutex_lock(&baguette[right]);
            mutex_lock(&baguette[left]);
        }
        mange(id);
        mutex_unlock(&baguette[left]);
        mutex_unlock(&baguette[right]);
    }
    return (NULL);
}

int main(int argc, char* argv[]) {


    PHILOSOPHES = atoi(argv[1]) ;
    if (PHILOSOPHES <= 1) return 0;

    phil = (pthread_t*) malloc(sizeof(pthread_t) * PHILOSOPHES);
    baguette = (mutex_t*) malloc(sizeof(mutex_t) * PHILOSOPHES);
    for (int i = 0; i<PHILOSOPHES;i++){
        mutex_init(&baguette[i]);
    }
    for (int i = 0 ; i<PHILOSOPHES ; i++) {
        int id  = i ;
        pthread_create(&(phil[i]), NULL, philosophe, &id) ;
    }
    for (int i = 0 ; i<PHILOSOPHES ; i++) {
        pthread_join(phil[i], NULL) ;
    }
    free(phil) ;
    free(baguette) ;
}
