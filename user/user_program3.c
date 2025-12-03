// user/user_program3.c
#include "syscall.h"

void user_program3(void *arg) {
    (void)arg;
    sys_print("[P3] starting... (CPU hog)\n");

    for (int i = 0; i < 3; i++) {
        sys_print("[P3] working...\n");
        // Could yield or not, to show starvation vs fairness.
        sys_yield();
    }

    sys_print("[P3] done.\n");
}