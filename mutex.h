

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <math.h>


#ifndef TEST_AND_SET_H
#define TEST_AND_SET_H

typedef struct mutex_t{
	int free;
} mutex_t;

/**
 * initializes the mutex
**/

int mutex_init(mutex_t *mutex);

int mutex_lock(mutex_t *mutex);

int mutex_unlock(mutex_t *mutex);


#endif //TEST_AND_SET_H
