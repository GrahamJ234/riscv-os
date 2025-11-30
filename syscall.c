// syscall.c
#include "syscall.h"
#include "proc.h"

// Reuse kernel-side puts; later you could enforce privilege modes.
extern void puts(const char *s);

void syscall_init(void) { }

void sys_print(const char *s) {
    puts(s);
}

int sys_getpid(void) {
    return get_current_pid();
}

int sys_create_file(const char *name, const char *content) {
    return fs_create(name, content);
}

int sys_read_file(const char *name, char *buf, int bufsize) {
    return fs_read(name, buf, bufsize);
}

void sys_yield(void) {
    proc_yield();
}
