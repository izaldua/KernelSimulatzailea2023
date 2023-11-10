#ifndef DATAEGITURAK_H
#define DATAEGITURAK_H

/**
 * @brief Gure PCB guztiak gordeko dituen ilara bakarra.
*/
struct ProcessQueue
{
    struct PCB *first; /**< Ilararen lehen PCB-aren helbidea. */
    int n; /**< Gure ilarak gordeta dituen PCB kopurua*/
};

struct PCB
{
    struct PCB *next;
    int id;
    int state;
    int priority; // Prozesu bakoitzaren niece-a izango da hau
    int quantum; // Quantuma, jakiteko prozesiu bakoitza zenbat denbora segidan egon leiken prozesadorean, hau aldatzen joango da
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