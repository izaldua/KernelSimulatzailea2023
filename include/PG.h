#ifndef PG_H
#define PG_H

struct PCB* processCreate(int id, int state, int priority, int quantum, int TTL);
extern void *processGenerator();

#endif /* PG_H */