#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>
#include <unistd.h>

#include "../include/config.h"
#include "../include/timer.h"

sem_t sem_sc;
sem_t sem_pg;

void *timer_SD()
{
    printf("# Timer Scheduler: Ondo iritsi naiz timer-era.\n");
    while (1)
    {
        done++;
        pthread_mutex_lock(&mutex);

        sem_post(&sem_sc);

        pthread_cond_signal(&cond1);
        pthread_cond_wait(&cond2, &mutex);
    }
}

void *timer_PG()
{
    printf("# Timer Process Generator: Ondo iritsi naiz timer-era.\n");
    while (1)
    {
        done++;
        pthread_mutex_lock(&mutex);

        sem_post(&sem_pg);

        pthread_cond_signal(&cond1);
        pthread_cond_wait(&cond2, &mutex);
    }
}