// kernel.c
#include "proc.h"
#include "fs.h"
#include "sync.h"
#include "syscall.h"


extern void puts(const char *s);   // you’ll implement this via UART later


void user_program1(void *arg);
void user_program2(void *arg);
void user_program3(void *arg);


void kernel_main(void) {
   puts("RISC-V OS Starting...\n");
   puts("Initializing kernel...\n");


   proc_init();
   fs_init();
   sync_init();
   syscall_init();


   // “Load” some user programs (here we just point to functions)
   int pid1 = proc_create(user_program1, (void*)"P1");
   int pid2 = proc_create(user_program2, (void*)"P2");
   int pid3 = proc_create(user_program3, (void*)"P3");


   if (pid1 < 0 || pid2 < 0 || pid3 < 0) {
       puts("Failed to create some processes.\n");
   }


   puts("Starting scheduler...\n");
   scheduler_loop();  // never returns


   // should never get here
   while (1) { }
}
