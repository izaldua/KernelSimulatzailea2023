#ifndef DatuEgiturak_H
#define DatuEgiturak_H

/**
 * @brief Gure PCB guztiak gordeko dituen ilara bakarra.
*/

extern struct ProcessQueue queue;
struct ProcessQueue
{
    struct PCB *first; /**< Ilararen lehen PCB-aren helbidea. */
    struct PCB *last;
    int n; /**< Gure ilarak gordeta dituen PCB kopurua*/
};

struct PCB
{
    struct PCB *next;
    int id;
    int state;
    int priority; // Prozesu bakoitzaren niece-a izango da hau
    int quantum; // Quantuma, jakiteko prozesiu bakoitza zenbat denbora segidan egon leiken prozesadorean, hau aldatzen joango da
    int TTL;
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

void aldatuTTL(struct ProcessQueue *queue, int TTL);
void aldatuQuantum(struct ProcessQueue *queue);

void initQueue(struct ProcessQueue *queue);
void enqueue(struct ProcessQueue *queue, struct PCB *pcb);
struct PCB* dequeue(struct ProcessQueue *queue);
struct PCB* peek(struct ProcessQueue *queue);
int isEmpty(struct ProcessQueue *queue);
void moveBack(struct ProcessQueue *queue);

#endif /* DatuEgiturak_H */