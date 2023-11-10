#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

#include "../include/DataEgiturak.h"

void initQueue(struct ProcessQueue *queue){
    struct PCB pcb = {NULL, 0, 0, 0, 0};
    queue->first = &pcb;
    queue->n = 0;
}

void enqueue(struct ProcessQueue *queue, struct PCB *pcb)
{
    pcb->next = queue->first;
    queue->first = pcb;
    queue->n++;
}

struct PCB dequeue(struct ProcessQueue *queue, struct PCB *pcb)
{
    struct PCB lag = *(queue->first);
    queue->first = queue->first->next;
    queue->n--;
    return lag;
}

struct PCB peek(struct ProcessQueue *queue, struct PCB *pcb)
{
    return *(queue->first);
}

/*
int isFull()
{
}
*/

/**
 * Funtzio honek ilaran elementu erabilgarririk dagoen adierazten gaitu
 * 1-koa itzuliko digu ilara "hutsik egon ezkero
 * 0-koa itzuliko digu ilaran elementu bat egon ezkero"
 * @param queue Aztertu nahi den ilara
 * @return Ilararen egoera, elementurik dagoen edo ez, 0 edo 1 emaitzat
 */ 
int isEmpty(struct ProcessQueue *queue) 
{
    if(queue->n == 0) return 1;
    else return 0;
}