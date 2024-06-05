#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

#include "../include/config.h"
#include "../include/PG.h"
#include "../include/DatuEgiturak.h"

struct PCB* processCreate(int id, int state, int priority, int quantum, int TTL)
{
    struct PCB *pcb = (struct PCB *)malloc(sizeof(struct PCB));
    if (pcb == NULL)
    {
        printf("Arazoa prozesua sortzerako orduan\n");
        return NULL;
    } 

    pcb->id = id;
    pcb->state = state;
    pcb->priority = priority;
    pcb->quantum = quantum;
    pcb->TTL = TTL;
    pcb->next = NULL;

    return pcb;
} 

void *processGenerator()
{

    int tick = 0;
    while (1)
    {
        sem_wait(&sem_pg);

        printf("\nPG : %d", tick);
        if (id < 100){
            struct PCB *pcb = processCreate(id, 0, 0, 0, TTL);
            enqueue(&queue, pcb);
            id++;
        } 
        usleep(PGF);

        tick++;
    }
}