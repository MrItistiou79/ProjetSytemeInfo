#ifndef PROJETSYTEMEINFO_MUTEX_H
#define PROJETSYTEMEINFO_MUTEX_H

typedef struct mutex{
	int free;
} mutex_t;


int mutex_init(mutex_t *mutex);

int mutex_lock(mutex_t *mutex);

int mutex_unlock(mutex_t *mutex);

#endif //PROJETSYTEMEINFO_MUTEX_H
