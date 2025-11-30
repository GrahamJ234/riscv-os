// syscall.h
#ifndef SYSCALL_H
#define SYSCALL_H

#include "fs.h"

void syscall_init(void);

// "user-level" API
void sys_print(const char *s);
int  sys_getpid(void);
int  sys_create_file(const char *name, const char *content);
int  sys_read_file(const char *name, char *buf, int bufsize);
void sys_yield(void);

#endif
