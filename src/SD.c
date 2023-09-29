#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

#include "../include/config.h"
#include "../include/SD.h"

void *scheduler()
{

    int tick = 0;

    while (1)
    {
        sem_wait(&sem_sc);

        printf("\nSD : %d", tick);
        tick++;
    }
}