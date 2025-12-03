// user/user_program1.c
#include "syscall.h"

void user_program1(void *arg) {
    (void)arg;
    sys_print("[P1] starting...\n");
    sys_create_file("hello.txt", "Hello from P1!");

    for (int i = 0; i < 5; i++) {
        sys_print("[P1] tick\n");
        sys_yield();
    }

    sys_print("[P1] done.\n");
}
