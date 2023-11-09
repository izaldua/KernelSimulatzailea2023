#ifndef DATAEGITURAK_H
#define DATAEGITURAK_H

struct ProcessQueue
{
    struct PCB *first;
    int n;
};

struct PCB
{
    struct PCB *next;
    int id;
    int state;
    int priority;
    // int PC;
    // int Context Data;
    // int Memory;
    // int I/O;
    // int Accounting;
};

struct Haria
{
    struct Haria *next;
};

struct Core
{
    struct Core *next;
    struct Haria *first;
};

struct CPU
{
    struct CPU *next;
    struct Core *first;
};

struct Machine
{
    struct CPU *first;
};

struct PCB;
struct Haria;
struct CPU;
struct Core;
struct Machine;

void initQueue(struct ProcessQueue *queue);
void enqueue(struct ProcessQueue *queue, struct PCB *pcb);
struct PCB dequeue(struct ProcessQueue *queue, struct PCB *pcb);
struct PCB peek(struct ProcessQueue *queue, struct PCB *pcb);
int isEmpty(struct ProcessQueue *queue);

#endif /* DATAEGITURAK_H */