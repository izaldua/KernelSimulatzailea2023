#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

#include "../include/config.h"
#include "../include/erlojua.h"

void *erlojua()
{
    printf("# Erlojua: Ondo iritsi naiz erlojura.\n");
    done = 0;
    while (1)
    {
        pthread_mutex_lock(&mutex);
        while (done < TENP_KOP)
        {
            pthread_cond_wait(&cond1, &mutex);
        }
        done = 0;
        pthread_cond_broadcast(&cond2);
        pthread_mutex_unlock(&mutex);
    }
}