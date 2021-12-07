#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <math.h>
#include "mutex.h"
#include "sem.h"

int* buffer ;
mutex_t *mutex ;
mutex_t *mutex2 ;
sem_t *empty ;
sem_t *full ;
int put_idx ;
int get_idx ;
int n_created ;
int n_consumer ;
int n_producer ;

void put_item(int test) {
    buffer[put_idx] = test ;
    put_idx = (put_idx + 1)%8 ;
}

int get_item() {
    int test = buffer[get_idx] ;
    get_idx = (get_idx + 1)%8 ;
    return test ;
}

int create_data(){
    while(mutex2->free){}
    mutex_lock(mutex2) ;
    n_created ++ ;
    int n  = n_created ;
    mutex_unlock(mutex2) ;
    if (n <= 1024) {
        while (rand() > RAND_MAX/10000){}
    }
    return n ;

}

void process_data(){
    while (rand() > RAND_MAX/10000){}
}

void* producer(void* arg) {
    bool test = true ;
    while (test) {
        int check = create_data() ;
        sema_wait(empty);
        while(mutex->free){}
        mutex_lock(mutex);
        put_item(check);
        mutex_unlock(mutex);
        sema_post(full);
        if (check > 1024 + n_consumer - n_producer) {
            test = false ;
        }
    }
    return NULL ;
}

void* consumer(void* arg) {
    bool test = true ;
    while (test) {
        sema_wait(full);
        while(mutex->free){}
        mutex_lock(mutex);
        int check = get_item();
        mutex_unlock(mutex);
        sema_post(empty);
        if (check <= 1024) {
            process_data();
        }
        else {
            test = false ;
        }
    }
    return NULL;
}

int main(int argc, char* argv[]) {
    int n_threads = atoi(argv[1]);

    n_producer = floor(n_threads/2);
    n_consumer = ceil(n_threads/2);


    pthread_t* producers = (pthread_t *)malloc(sizeof(pthread_t)*n_producer) ;
    pthread_t* consumers = (pthread_t *)malloc(sizeof(pthread_t)*n_consumer) ;
    put_idx = 0 ;
    get_idx = 0 ;
    n_created = 0 ;

    buffer  = (int*) malloc(sizeof(int)*8) ;
    mutex = (mutex_t*)malloc(sizeof(mutex_t)) ;
    mutex2 = (mutex_t*)malloc(sizeof(mutex_t)) ;
    mutex_init(mutex) ;
    mutex_init(mutex2) ;

    full = malloc(sizeof(sem_t)) ;
    empty = malloc(sizeof(sem_t)) ;
    sema_init(full, 0) ;
    sema_init(empty, 8) ;

    for (int i = 0 ; i<n_producer ; i++) {
        pthread_create(&producers[i], NULL, producer, NULL) ;
    }
    for (int i = 0 ; i<n_consumer ; i++) {
        pthread_create(&consumers[i], NULL, consumer, NULL) ;
    }
    for (int i = 0 ; i<n_producer ; i++) {
        pthread_join(producers[i], NULL) ;
    }
    for (int i = 0 ; i<n_consumer ; i++) {
        pthread_join(consumers[i], NULL) ;
    }

    free(buffer) ;
    free(producers) ;
    free(consumers) ;
    free(mutex) ;
    free(mutex2) ;
    free(full) ;
    free(empty) ;
}
