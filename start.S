    .section .text.entry
    .globl _start
_start:
    # Set up stack pointer (just pick some address in RAM above end of .bss)
    la   sp, _stack_top

    # Zero .bss (optional but nice)
    la   t0, _bss_start
    la   t1, _bss_end
1:
    bgeu t0, t1, 2f
    sw   zero, 0(t0)
    addi t0, t0, 4
    j    1b
2:
    # Call kernel_main()
    la   a0, boot_msg
    jal  ra, kernel_main

    # If kernel_main returns, just spin
hang:
    j    hang

    .section .rodata
boot_msg:
    .asciz "RISC-V OS starting...\n"

    .section .bss
    .globl _bss_start
_bss_start:
    .space 4
    .globl _bss_end
_bss_end:

    .section .bss
    .align 4
    .globl _stack
_stack:
    .space 4096
    .globl _stack_top
_stack_top:
