// uart.c
#define UART0_BASE 0x10000000UL
#define UART0_THR  (UART0_BASE + 0)
#define UART0_LSR  (UART0_BASE + 5)
#define UART_LSR_THRE 0x20

static void uart_putc(char c) {
    volatile unsigned char *thr = (unsigned char*)UART0_THR;
    volatile unsigned char *lsr = (unsigned char*)UART0_LSR;
    while (!(*lsr & UART_LSR_THRE)) { }
    *thr = c;
}

void puts(const char *s) {
    while (*s) {
        if (*s == '\n') {
            uart_putc('\r');
        }
        uart_putc(*s++);
    }
}