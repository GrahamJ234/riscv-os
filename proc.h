// proc.h
#ifndef PROC_H
#define PROC_H

#define MAX_PROCS   8
#define STACK_SIZE  4096

typedef enum {
    PROC_UNUSED = 0,
    PROC_READY,
    PROC_RUNNING,
    PROC_BLOCKED,
    PROC_ZOMBIE
} proc_state_t;

typedef void (*entry_fn_t)(void*);

typedef struct {
    int         pid;
    proc_state_t state;
    entry_fn_t  entry;
    void       *arg;
    unsigned char *stack;   // stack base
    unsigned char *sp;      // saved stack pointer (for context switch)
} proc_t;

void proc_init(void);
int  proc_create(entry_fn_t entry, void *arg);
void scheduler_loop(void);
void proc_yield(void);
int  get_current_pid(void);

#endif
