#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>
#include <unistd.h>

#include "../include/config.h"
#include "../include/timer.h"

sem_t sem_sc;
sem_t sem_pg;

void *timer_SD(long *SDF)
{
    int frek = 0;
    int ticksd = 0;
    printf("# Timer Scheduler: Ondo iritsi naiz timer-era.\n");
    pthread_mutex_lock(&mutex);
    while (1)
    {
        done++;
        ticksd++;
        if (frek == *SDF)
        {
            sem_post(&sem_sc);
            frek = 0;
        } else frek++;

        pthread_cond_signal(&cond1);
        if (finalize) return 0;
        pthread_cond_wait(&cond2, &mutex);
        if (finalize) return 0;
    }
}

void *timer_PG(long *PGF)
{
    printf("# Timer Process Generator: Ondo iritsi naiz timer-era.\n");
    int frek = 0;
    int tickpg = 0;
    pthread_mutex_lock(&mutex);
    while (1)
    {
        done++;
        tickpg++;
        if (frek == *PGF)
        {
            sem_post(&sem_pg);
            frek = 0;
        } else frek++;

        pthread_cond_signal(&cond1);
        if (finalize) return 0;
        pthread_cond_wait(&cond2, &mutex);
        if (finalize) return 0;
    }
}