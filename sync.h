// sync.h
#ifndef SYNC_H
#define SYNC_H

typedef struct {
    int locked;
} mutex_t;

typedef struct {
    int count;
} sem_t;

void sync_init(void);

void mutex_init(mutex_t *m);
void mutex_lock(mutex_t *m);
void mutex_unlock(mutex_t *m);

void sem_init(sem_t *s, int value);
void sem_wait(sem_t *s);
void sem_post(sem_t *s);

#endif
