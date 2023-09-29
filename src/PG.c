#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

#include "../include/config.h"
#include "../include/PG.h"

void *processGenerator()
{

    int tick = 0;

    while (1)
    {
        sem_wait(&sem_pg);

        printf("\nPG : %d", tick);
        tick++;
    }
}