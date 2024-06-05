#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

#include "../include/DatuEgiturak.h"

struct ProcessQueue queue;

void aldatuTTL(struct ProcessQueue *queue, int TTL)
{
    queue->first->TTL = TTL;
} 

void aldatuQuantum(struct ProcessQueue *queue)
{
    if (queue->first->quantum < 32)queue->first->quantum = queue->first->quantum*2;
    else queue->first->quantum = 32;
}

void initQueue(struct ProcessQueue *queue){
    struct PCB *nullProcess = (struct PCB *)malloc(sizeof(struct PCB));
    nullProcess->next = NULL;
    nullProcess->id = -1;
    nullProcess->state = 0;
    nullProcess->priority = 0;
    nullProcess->quantum = 0;
    nullProcess->TTL = 0;

    queue->first = nullProcess;
    queue->last = nullProcess;
    queue->n = 0;
}

void enqueue(struct ProcessQueue *queue, struct PCB *pcb)
{
    pcb->next = NULL;
    if (queue->last->id == -1 && queue->first->id == -1){
        queue->first = pcb;
        queue->last = pcb;
    } else {
        queue->last->next = pcb;
        queue->last = pcb;
    } 
    queue->n++;
}

struct PCB* dequeue(struct ProcessQueue *queue)
{
    if(queue->first->id == -1 && queue->last->id == -1) return NULL;
    
    struct PCB *lag = queue->first;
    queue->first = queue->first->next;
    if(queue->first == NULL) initQueue(queue);
    queue->n--;
    return lag;
}

struct PCB* peek(struct ProcessQueue *queue)
{
    return queue->first;
}

/**
 * Funtzio honek ilaran elementu erabilgarririk dagoen adierazten gaitu
 * 1-koa itzuliko digu ilara "hutsik egon ezkero
 * 0-koa itzuliko digu ilaran elementu bat egon ezkero"
 * @param queue Aztertu nahi den ilara
 * @return Ilararen egoera, elementurik dagoen edo ez, 0 edo 1 emaitzat
 */ 
int isEmpty(struct ProcessQueue *queue) 
{
    if(queue->first->id == -1 && queue->last->id == -1) return 1;
    else return 0;
}


void moveBack(struct ProcessQueue *queue)
{
    struct PCB *lag = queue->first;
    struct PCB *lead = queue->first->next;
    queue->first = lead;
    queue->last->next = lag;
    queue->last = lag;
    queue->last->next = NULL;
}
