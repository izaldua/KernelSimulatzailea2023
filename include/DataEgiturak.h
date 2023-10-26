#ifndef DATAEGITURAK_H
#define DATAEGITURAK_H

struct ProcessQueue
{
    struct PCB *first;
    struct PCB *last;
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

#endif /* DATAEGITURAK_H */