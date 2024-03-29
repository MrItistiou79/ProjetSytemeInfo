
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <math.h>
#include "mutex.h"

pthread_t *threads;
mutex_t* mutex;
int n_threads;
int cycle;
int sectionCritique(){
    while (rand() > RAND_MAX/10000){}
}

void * run(){
    int count = 0;
    while (count <= 6400/n_threads){
        while(mutex->free){}
        mutex_lock(mutex);
        cycle++;
        sectionCritique();
        mutex_unlock(mutex);
        count++;
    }
}

int main(int argc, char* argv[]){
    n_threads = atoi(argv[1]);

    mutex = (mutex_t*)malloc(sizeof(mutex_t));
    mutex_init(mutex);
    threads = (pthread_t*) malloc(sizeof(pthread_t) * n_threads);
    cycle = 0;

    for (int i = 0 ; i<n_threads ; i++) {
        int id  = i ;
        pthread_create(&(threads[i]), NULL, run, &id) ;
    }

    for (int i = 0 ; i<n_threads ; i++) {
        pthread_join(threads[i], NULL) ;
    }

    free(threads);
    return 0;
}
