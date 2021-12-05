#include <semaphore.h>
#include <pthread.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>
#include <stdbool.h>
#include <math.h>

pthread_mutex_t *mutex ;
sem_t *wsem;

pthread_mutex_t *mutex2 ;
sem_t *rsem;

pthread_mutex_t *z ;

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
        pthread_mutex_lock(mutex2) ;
        writecount ++ ;
        if (writecount == 1) {
            sem_wait(rsem) ;
        }
        pthread_mutex_unlock(mutex2) ;
        sem_wait(wsem) ;
        write_database() ;

        sem_post(wsem) ;

        pthread_mutex_lock(mutex2) ;
        writecount -- ;
        if (writecount == 0) {
            sem_post(rsem) ;
        }
        pthread_mutex_unlock(mutex2) ;
        writings ++ ;
    }
    return NULL ;
}

void* reader(void* arg) {
    int readings = 0 ;
    while(readings < 2560) {
        pthread_mutex_lock(z) ; // mutex z pour qu'il puisse y avoir que 1 reader en attente sur rsem.
        sem_wait(rsem) ;

        pthread_mutex_lock(mutex) ;
        readcount ++ ;
        if (readcount == 1) { // arrivée du premier reader
            sem_wait(wsem) ;
        }
        pthread_mutex_unlock(mutex) ;

        sem_post(rsem) ; // libération du prochain reader
        pthread_mutex_unlock(z) ;
        read_database() ;

        pthread_mutex_lock(mutex) ;
        readcount --;
        if (readcount == 0) { // si plus de reader, libere writer
            sem_post(wsem) ;
        }
        pthread_mutex_unlock(mutex) ;
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
    
    

    
    mutex = malloc(sizeof(pthread_mutex_t)) ;
    mutex2 = malloc(sizeof(pthread_mutex_t)) ;
    z = malloc(sizeof(pthread_mutex_t)) ;
    pthread_mutex_init(mutex, NULL) ;
    pthread_mutex_init(mutex2, NULL) ;
    pthread_mutex_init(z, NULL) ;
    wsem = malloc(sizeof(sem_t)) ;
    rsem = malloc(sizeof(sem_t)) ;
    sem_init(wsem, 0, 1) ;
    sem_init(rsem, 0, 1) ;
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
    sem_destroy(wsem) ;
    sem_destroy(rsem) ;
    free(readers) ;
    free(writers) ;
    free(mutex) ;
    free(mutex2) ;
    free(z) ;
    free(wsem) ;
    free(rsem) ;
}
