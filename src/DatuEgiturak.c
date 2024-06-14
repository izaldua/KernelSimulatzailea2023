#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

#include "../include/DatuEgiturak.h"

struct ProcessQueue queue;

void initMachine(struct Machine *machine, int hariKop, int coreKop, int cpuKop)
{
    struct  CPU *cpu = (struct CPU *)malloc(sizeof(struct CPU));

    cpu->next = NULL;
    for (int i = 0; i < cpuKop; i++)
    {
        struct CPU *newCPU = (struct CPU *)malloc(sizeof(struct CPU));
        newCPU->next = NULL;
        cpu->next = newCPU;
        cpu = newCPU;
        struct Core *core = (struct Core *)malloc(sizeof(struct Core));
        core->next = NULL;
        cpu->first = core;
        for (int j = 0; j < coreKop; j++)
        {
            struct Core *newCore = (struct Core *)malloc(sizeof(struct Core));
            newCore->next = NULL;
            core->next = newCore;
            core = newCore;
            struct Haria *haria = (struct Haria *)malloc(sizeof(struct Haria));
            haria->next = NULL;
            core->first = haria;
            for (int k = 0; k < hariKop; k++)
            {
                struct Haria *newHaria = (struct Haria *)malloc(sizeof(struct Haria));
                newHaria->next = NULL;
                haria->next = newHaria;
                haria = newHaria;
            }
        }
    }
}

void destroyMachine(struct Machine *machine)
{
    struct CPU *cpu = machine->first;
    while (cpu != NULL)
    {
        struct CPU *lagCPU = cpu;
        struct Core *core = cpu->first;
        while (core != NULL)
        {
            struct Core *lagCore = core;
            struct Haria *haria = core->first;
            while (haria != NULL)
            {
                struct Haria *lagHaria = haria;
                haria = haria->next;
                free(lagHaria);
            }
            core = core->next;
            free(lagCore);
        }
        cpu = cpu->next;
        free(lagCPU);
    }
}

uint32_t* init_orria(){
    uint32_t* orria = (uint32_t *) malloc (10 * sizeof(uint32_t));
    if (orria == NULL){
        printf("\nErrorea orria hasieratzeko orduan\n");
        exit(1);
    } 

    for (int i = 0; i < 10; i++) orria[i] = 0;  

    return orria;   
} 

void free_orria(uint32_t *orria){
    free(orria);
    orria = NULL;
} 

uint32_t* init_erregistroak (){
    uint32_t* erregistroa = (uint32_t *) malloc (16 * sizeof(uint32_t)); 

    if (erregistroa == NULL){
        printf("\nErrorea erregistroak hasieratzeko orduan\n");
        exit(1);
    } 

    for (int i = 0; i < 16; i++) erregistroa[i] = 0; 

    return erregistroa;
} 

void free_erregistroak (uint32_t *erregistroa){
    free(erregistroa);
    erregistroa = NULL;
} 

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
