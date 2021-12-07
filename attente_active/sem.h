#ifndef PROJETSYTEMEINFO_SEM_H
#define PROJETSYTEMEINFO_SEM_H

#include "mutex.h"

typedef struct sem{
	int val;
	mutex_t *mutex;
}sem_t;


int sema_init(sem_t *sem, int val);

int sema_wait(sem_t *sem);

int sema_post(sem_t *sem);
#endif //PROJETSYTEMEINFO_SEM_H
