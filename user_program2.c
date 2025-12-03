// user/user_program2.c
#include "syscall.h"

void user_program2(void *arg) {
    (void)arg;
    sys_print("[P2] starting...\n");

    char buf[64];
    int len = sys_read_file("hello.txt", buf, sizeof(buf));
    if (len > 0) {
        sys_print("[P2] read: ");
        sys_print(buf);
        sys_print("\n");
    } else {
        sys_print("[P2] could not read hello.txt\n");
    }

    for (int i = 0; i < 5; i++) {
        sys_print("[P2] tick\n");
        sys_yield();
    }

    sys_print("[P2] done.\n");
}