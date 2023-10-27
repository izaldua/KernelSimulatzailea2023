#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

#include "../include/DataEgiturak.h"

void initQueue(struct ProcessQueue *queue)
{
    queue->first = NULL;
    queue->last = NULL;
    queue->n = 0;
}

void enqueue(struct PCB *newpcb, struct ProcessQueue *queue)
{
    newpcb->next == NULL;
    if (queue->first == NULL)
        queue->first = newpcb;
    else
    {
        queue->last->next = newpcb;
        queue->last = newpcb;
    }
    queue->n++;
}

struct PCB dequeue(struct ProcessQueue *queue)
{
    struct PCB lag = {NULL, NULL, NULL};
    if (queue->first == NULL)
        return lag;
    else
    {
        lag = *queue->first;
        queue->first = queue->first->next;
    }
    queue->n--;
}

struct PCB peek(struct ProcessQueue *queue)
{
    struct PCB lag = {NULL, NULL, NULL};
    if (queue->first == NULL)
        return lag;
    else
        return *queue->first;
}

int isEmpty(struct ProcessQueue *queue)
{
    return queue->first == NULL;
}