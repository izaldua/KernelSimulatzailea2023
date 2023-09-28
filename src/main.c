#include <stdio.h>
#include <pthread.h>

#include "config.h"
#include "clock.h"
#include "timer.h"

pthread_t erl, tim;

int main(int argc, char *argv[])
{
 
    printf("\n\n===========SISTEMA ONDO HASIERATUA===========\n\n");

    if (pthread_create(&erl, NULL, (void *)clock, NULL) != 0)
    {
        perror("Failed to create threads");
        exit();
    } // Hariak sortzeko momentuan existitzen badira dagoeneko, honek "errorea" bueltatuko du

    if (pthread_create(&tim, NULL, (void *)timer, NULL) != 0)
    {
        perror("Failed to create threads");
        exit();
    }
}