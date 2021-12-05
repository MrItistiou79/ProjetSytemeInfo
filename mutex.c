#include "mutex.h"


int main(){
	return 0;
}


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
		: "%eax", "memory"
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
		: "%eax", "memory"
	);
	return 0;
}

