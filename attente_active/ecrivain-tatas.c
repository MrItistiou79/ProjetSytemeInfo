#include "sem.h"
#include "mutex.h"
#include <pthread.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <stdbool.h>
#include <math.h>

mutex_t *mutex ;
sem_t *wsem;

mutex_t *mutex2 ;
sem_t *rsem;

mutex_t*z ;

int readcount ;
int writecount ;

void read_database() {
    while (rand() > RAND_MAX/10000){}
}

void write_database() {
    while (rand() > RAND_MAX/10000){}
}

void* writer(void* arg) {
    int writings = 0 ;
    while (writings < 640) {
        while(mutex2->free){}
        mutex_lock(mutex2) ;
        writecount ++ ;
        if (writecount == 1) {
            sema_wait(rsem) ;
        }
        mutex_unlock(mutex2) ;
        sema_wait(wsem) ;
        write_database() ;

        sema_post(wsem) ;

        while(mutex2->free){}
        mutex_lock(mutex2) ;
        writecount -- ;
        if (writecount == 0) {
            sema_post(rsem) ;
        }
        mutex_unlock(mutex2) ;
        writings ++ ;
    }
    return NULL ;
}

void* reader(void* arg) {
    int readings = 0 ;
    while(readings < 2560) {
        while(z->free){}
        mutex_lock(z) ; // mutex z pour qu'il puisse y avoir que 1 reader en attente sur rsem.
        sema_wait(rsem) ;

        while(mutex->free){}
        mutex_lock(mutex) ;
        readcount ++ ;
        if (readcount == 1) { // arrivée du premier reader
            sema_wait(wsem) ;
        }
        mutex_unlock(mutex) ;

        sema_post(rsem) ; // libération du prochain reader
        mutex_unlock(z) ;
        read_database() ;

        while(mutex->free){}
        mutex_lock(mutex) ;
        readcount --;
        if (readcount == 0) { // si plus de reader, libere writer
            sema_post(wsem) ;
        }
        mutex_unlock(mutex) ;
        readings ++ ;
    }
    return NULL ;
}

int main(int argc, char* argv[]) {
    readcount = 0 ;
    writecount = 0 ;

    int n_threads = atoi(argv[1]) ;

    int n_readers = floor(n_threads/2);
    int n_writers = ceil(n_threads/2);

    mutex = malloc(sizeof(mutex_t)) ;
    mutex2 = malloc(sizeof(mutex_t)) ;
    z = malloc(sizeof(mutex_t)) ;

    mutex_init(mutex) ;
    mutex_init(mutex2) ;
    mutex_init(z) ;

    wsem = malloc(sizeof(sem_t)) ;
    rsem = malloc(sizeof(sem_t)) ;
    sema_init(wsem, 1) ;
    sema_init(rsem, 1) ;

    pthread_t* writers = (pthread_t *) malloc(sizeof(pthread_t)*n_writers) ;
    pthread_t* readers = (pthread_t *) malloc(sizeof(pthread_t)*n_readers) ;


    for (int i = 0 ; i<n_writers ; i++) {
        pthread_create(&writers[i], NULL, writer, NULL) ;
    }
    for (int i = 0 ; i<n_readers ; i++) {
        pthread_create(&readers[i], NULL, reader, NULL) ;
    }
    for (int i = 0 ; i<n_writers ; i++) {
        pthread_join(writers[i], NULL) ;
    }
    for (int i = 0 ; i<n_readers ; i++) {
        pthread_join(readers[i], NULL) ;
    }
    free(wsem);
    free(rsem);
    free(readers) ;
    free(writers) ;
    free(mutex) ;
    free(mutex2) ;
    free(z) ;
}
