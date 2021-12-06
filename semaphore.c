
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <math.h>


typedef struct sem{
	int val;
	mutex_t *mutex;
}sem_t


int sema_init(sem_t *sem, int val){
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
		}
		mutex_unlock(sem->mutex);
	}

}

int sema_post(sem_t sem){
	mutex_lock(sem->mutex);
	sem->val++;
	mutex_unlock(sem->mutex);
}

