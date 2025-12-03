    .section .text.entry
    .globl _start

_start:
    # Set up stack pointer
    la   sp, _stack_top

    # Call C kernel entry
    call kernel_main

1:
    j 1b          # if kernel_main returns, spin forever


    .section .bss
    .align 4
    .globl _stack
_stack:
    .space 4096          # 4 KB stack

    .globl _stack_top
_stack_top: