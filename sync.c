// sync.c
#include "sync.h"
#include "proc.h"

void sync_init(void) { }

void mutex_init(mutex_t *m) {
    m->locked = 0;
}

void mutex_lock(mutex_t *m) {
    // simple spinlock; with yield for “friendliness”
    while (__sync_lock_test_and_set(&m->locked, 1)) {
        proc_yield();
    }
}

void mutex_unlock(mutex_t *m) {
    __sync_lock_release(&m->locked);
}

void sem_init(sem_t *s, int value) {
    s->count = value;
}

void sem_wait(sem_t *s) {
    while (1) {
        if (s->count > 0) {
            // Attempt to decrement atomically
            int old = __sync_fetch_and_sub(&s->count, 1);
            if (old > 0) return;
            // if old <= 0, we “stole” badly; fix and continue
            __sync_fetch_and_add(&s->count, 1);
        }
        proc_yield();
    }
}

void sem_post(sem_t *s) {
    __sync_fetch_and_add(&s->count, 1);
}
