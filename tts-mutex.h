
#ifndef TTS_MUTEX_H
#define TTS_MUTEX_H

#include <stdlib.h>

typedef struct mutex{
	int free;
}tts_mutex;

/**
 * initializes the mutex
**/

int tts_mutex_init(tts_mutex *mutex);

int tts_mutex_lock(tts_mutex *mutex);

int tts_mutex_unlock(tts_mutex *mutex);


#endif //TTS_MUTEX_H
