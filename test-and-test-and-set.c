
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <math.h>

typedef struct mutex_t{
    int free;
} mutex_t;

pthread_t *threads;
mutex_t* mutex;
int n_threads;
int cycle;



int mutex_init(mutex_t *mutex){
    mutex->free = 0;
    return 0;
}

int mutex_lock(mutex_t *mutex){
    __asm__ __volatile__
    (
    "enter:\n\t"
    "movl $1, %%eax;\n\t"
    "xchgl %%eax, %0;\n\t"
    "testl %%eax, %%eax;\n\t"
    "jnz enter;\n\t"
    :
    : "m" (mutex->free)
    : "%eax"
    );
    return 0;
}

int mutex_unlock(mutex_t *mutex){
    __asm__ __volatile__
    (
    "leave:\n\t"
    "movl $0, %%eax;\n\t"
    "xchgl %%eax, %0;\n\t"
    :
    : "m" (mutex->free)
    : "%eax"
    );
    return 0;
}

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
