#ifndef DatuEgiturak_H
#define DatuEgiturak_H

#include <stdint.h> 

#define MEMORIA_TAMAINA 0x1000000

/**
 * @brief Gure PCB guztiak gordeko dituen ilara bakarra.
*/
extern struct ProcessQueue queue;

extern uint32_t erregistroa; 

struct ProcessQueue
{
    struct PCB *first; /**< Ilararen lehen PCB-aren helbidea. */
    struct PCB *last;
    int n; /**< Gure ilarak gordeta dituen PCB kopurua*/
};

struct mm
{
    uint32_t data;
    uint32_t code;
    uint32_t pgb;
}; 

struct PCB
{
    struct PCB *next;
    int id;
    int state;
    int priority; // Prozesu bakoitzaren niece-a izango da hau
    int quantum; // Quantuma, jakiteko prozesiu bakoitza zenbat denbora segidan egon leiken prozesadorean, hau aldatzen joango da
    int TTL;
    struct mm mm;
    // int Context Data;
    // int Memory;
    // int I/O;
    // int Accounting;
};

struct Haria
{
    struct Haria *next;
    uint32_t PC;
    uint32_t IR;
    uint32_t PTBR;
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

void initMachine(struct Machine *machine, int cpuKop, int coreKop, int hariKop);
void destroyMachine(struct Machine *machine);

void aldatuTTL(struct ProcessQueue *queue, int TTL);
void aldatuQuantum(struct ProcessQueue *queue);

void initQueue(struct ProcessQueue *queue);
void enqueue(struct ProcessQueue *queue, struct PCB *pcb);
struct PCB* dequeue(struct ProcessQueue *queue);
struct PCB* peek(struct ProcessQueue *queue);
int isEmpty(struct ProcessQueue *queue);
void moveBack(struct ProcessQueue *queue);

#endif /* DatuEgiturak_H */