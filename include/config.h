#ifndef CONFIG_H
#define CONFIG_H

#include <pthread.h>
#include <semaphore.h>

#define TENP_KOP 2

extern pthread_mutex_t mutex;
extern pthread_cond_t cond1, cond2;

extern sem_t sem_sc; 
extern sem_t sem_pg; 

extern int done;
extern int freq;

extern long clockF;
extern long SDF;
extern long PGF;
extern int TTL;

//extern struct ProcessQueue queue;

#endif /* CONFIG_H */