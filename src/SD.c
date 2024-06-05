#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

#include "../include/config.h"
#include "../include/SD.h"
#include "../include/DatuEgiturak.h"

void prozesatu(struct ProcessQueue *queue)
{
    struct PCB *pcb = peek(queue); 
    int denbora = pcb->quantum;
    if (pcb != NULL)
    {
        printf("\nProzesatzen: id = %d, TTL = %d, quantuma = %d", pcb->id, pcb->TTL, pcb->quantum);
        //printf("\nHurrengo prozesua: id = %d, TTL = %d, quantuma = %d\n\n", peek(queue)->next->id, peek(queue)->next->TTL, peek(queue)->next->quantum);

        while (pcb->TTL > 0 && denbora > 0){
            sleep(1);
            denbora--;
            pcb->TTL--;
        } 

        if (pcb->TTL > 0){
            aldatuTTL(queue, pcb->TTL);
            aldatuQuantum(queue);
            moveBack(queue);
        } else {
            dequeue(queue);
            free(pcb);
        } 
    }
}

void *scheduler()
{
    int tick = 0;
    while (1)
    {
        sem_wait(&sem_sc);

        //printf("\nSD : %d", tick);
        usleep(SDF);
        prozesatu(&queue);

        tick++;
        //nola amaitu programa ?
        //if (isEmpty(&queue)) break;
    }
}