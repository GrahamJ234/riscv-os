// proc.c
#include "proc.h"
#include "sync.h"

static proc_t procs[MAX_PROCS];
static int current = -1;
static int next_pid = 1;

void proc_init(void) {
    for (int i = 0; i < MAX_PROCS; i++) {
        procs[i].state = PROC_UNUSED;
        procs[i].pid = -1;
        procs[i].stack = 0;
        procs[i].sp = 0;
    }
    current = -1;
    next_pid = 1;
}

// Forward decl – will be used as trampoline
static void proc_start_trampoline(void);

int proc_create(entry_fn_t entry, void *arg) {
    // Find free slot
    int idx = -1;
    for (int i = 0; i < MAX_PROCS; i++) {
        if (procs[i].state == PROC_UNUSED) {
            idx = i; break;
        }
    }
    if (idx < 0) return -1;

    // Allocate stack from static array
    static unsigned char stacks[MAX_PROCS][STACK_SIZE];
    procs[idx].stack = stacks[idx];
    procs[idx].entry = entry;
    procs[idx].arg   = arg;
    procs[idx].pid   = next_pid++;
    procs[idx].state = PROC_READY;

    // Initialize “stack pointer” to top of stack
    unsigned char *stack_top = procs[idx].stack + STACK_SIZE;

    // Fake initial stack frame so that when we “switch” to it, it calls proc_start_trampoline
    // Simplified: we’re not doing full register context here, just storing “return address”.
    stack_top -= sizeof(void*);
    *((void**)stack_top) = (void*)proc_start_trampoline;

    procs[idx].sp = stack_top;
    return procs[idx].pid;
}

static int pick_next_proc(void) {
    int start = current;
    for (int i = 0; i < MAX_PROCS; i++) {
        int idx = (start + 1 + i) % MAX_PROCS;
        if (procs[idx].state == PROC_READY) {
            return idx;
        }
    }
    return -1;
}

// This is a stand-in for a proper context switch. In real RISC-V, you'd
// save/restore registers, etc. Here we pretend we just jump to function.
static void context_switch(int next) {
    current = next;
    procs[current].state = PROC_RUNNING;
    // Call trampoline which then calls the entry function.
    proc_start_trampoline();
}

void scheduler_loop(void) {
    while (1) {
        int next = pick_next_proc();
        if (next < 0) {
            // No ready processes, idle spin
            // You might want an "idle" process instead.
            continue;
        }
        context_switch(next);
    }
}

void proc_yield(void) {
    // In a real OS, you'd save context and mark current as READY again.
    // Here we just mark it READY and let scheduler pick another.
    if (current >= 0 && procs[current].state == PROC_RUNNING) {
        procs[current].state = PROC_READY;
    }
    // scheduler_loop is driving things, so just return there.
}

int get_current_pid(void) {
    if (current < 0) return -1;
    return procs[current].pid;
}

// Trampoline runs the process entry and then marks it ZOMBIE
static void proc_start_trampoline(void) {
    int idx = current;
    if (idx < 0) return;
    procs[idx].entry(procs[idx].arg);
    procs[idx].state = PROC_ZOMBIE;
    // yield control back to scheduler
    proc_yield();
    while (1) { } // should never return
}
