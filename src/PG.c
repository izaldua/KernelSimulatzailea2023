#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

#include "../include/config.h"
#include "../include/PG.h"
#include "../include/DatuEgiturak.h"
#define AGINDU_KOP 3


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
    pcb->quantum = 1;
    pcb->TTL = rand() % TTL;
    pcb->next = NULL;

    return pcb;
} 

int id = 1; // id-ak esleitzeko nondik hasi behar den adieraztun du

void *processGenerator()
{

    int tick = 0;
    while (1)
    {
        sem_wait(&sem_pg);

        //printf("\nPG : %d", tick);
        if (id < AGINDU_KOP){
            struct PCB *pcb = processCreate(id, 0, 0, 0, TTL);
            enqueue(&queue, pcb);
            id++;
        } 
        if (finalize) return 0;
        usleep(PGF);

        tick++;
    }
}