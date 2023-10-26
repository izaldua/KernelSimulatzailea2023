#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

#include "../include/DataEgiturak.h"

void initQueue(struct ProcessQueue *queue){
    queue->first = NULL;
    queue->last = NULL;
    queue->n = 0;
}

void enqueue(struct PCB *pcb)
{
}

void dequeue()
{
}

struct PCB peek()
{
}

int isFull()
{
}

int isEmpty()
{
}