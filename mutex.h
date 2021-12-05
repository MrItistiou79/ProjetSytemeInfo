
#ifndef TEST_AND_SET_H
#define TEST_AND_SET_H

#include <stdlib.h>

typedef struct mutex{
	int free;
}mutex;

/**
 * initializes the mutex
**/

int mutex_init(mutex *mutex);


int mutex_lock(mutex *mutex);

int mutex_unlock(mutex *mutex);


#endif //TEST_AND_SET_H
