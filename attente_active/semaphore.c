
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <math.h>

#include "sem.h"



int sema_init(sem_t *sem, int val){
    sem->mutex = (mutex_t*)malloc(sizeof(mutex_t));
    mutex_init(sem->mutex);
    sem->val = val;
    return 0; 
	
}

int sema_wait(sem_t *sem){
	while (1){
		mutex_lock(sem->mutex);
		if (sem->val > 0){
			sem->val--;
			mutex_unlock(sem->mutex);	
			return 0; 
		}
		mutex_unlock(sem->mutex);
	}
}

int sema_post(sem_t *sem){
	mutex_lock(sem->mutex);
	sem->val++;
	mutex_unlock(sem->mutex);
	return 0; 
}

