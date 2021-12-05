#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

pthread_t *phil;
pthread_mutex_t *baguette;
int PHILOSOPHES;

void mange(int id) {}

void* philosophe (void* arg)
{
    int id=  *((int *) arg);
    int left = id;
    int right = (left + 1) % PHILOSOPHES;
    for (int i = 0 ; i<10000 ; i++) {
        // philosophe pense

        if(left<right) {
            pthread_mutex_lock(&baguette[left]);
            pthread_mutex_lock(&baguette[right]);
        }
        else {
            pthread_mutex_lock(&baguette[right]);
            pthread_mutex_lock(&baguette[left]);
        }
        mange(id);
        pthread_mutex_unlock(&baguette[left]);
        pthread_mutex_unlock(&baguette[right]);
    }
    return (NULL);
}

int main(int argc, char* argv[]) {

    
    PHILOSOPHES = atoi(argv[1]) ;
    
    if (PHILOSOPHES <= 1) return 0; 
    	
    phil = (pthread_t*) malloc(sizeof(pthread_t) * PHILOSOPHES);
    baguette = (pthread_mutex_t*) malloc(sizeof(pthread_mutex_t) * PHILOSOPHES);
    for (int i = 0 ; i<PHILOSOPHES ; i++) {
        int id  = i ;
        printf("hello\n");
        pthread_create(&(phil[i]), NULL, philosophe, &id) ;
    }
    for (int i = 0 ; i<PHILOSOPHES ; i++) {
        pthread_join(phil[i], NULL) ;
    }
    free(phil) ;
    free(baguette) ;
}
