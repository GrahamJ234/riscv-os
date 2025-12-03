CROSS  = riscv64-unknown-elf
CC     = $(CROSS)-gcc

CFLAGS = -O2 -Wall -ffreestanding -nostdlib -nostartfiles \
         -march=rv64imac -mabi=lp64 -mcmodel=medany -I.

LDFLAGS = -T linker.ld -nostdlib -nostartfiles \
          -march=rv64imac -mabi=lp64 -mcmodel=medany

SRCS = start.S kernel.c proc.c sync.c fs.c syscall.c uart.c mini_string.c \
       user/user_program1.c user/user_program2.c user/user_program3.c

OBJS = $(SRCS:.c=.o)
OBJS := $(OBJS:.S=.o)

all: os.elf

os.elf: $(OBJS) linker.ld
	$(CC) $(OBJS) $(LDFLAGS) -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

%.o: %.S
	$(CC) $(CFLAGS) -c -o $@ $<

run: os.elf
	qemu-system-riscv64 -machine virt -nographic -bios none -kernel os.elf

clean:
	rm -f $(OBJS) os.elf