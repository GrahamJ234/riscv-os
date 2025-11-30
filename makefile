CROSS = riscv32-unknown-elf
CC    = $(CROSS)-gcc
LD    = $(CROSS)-ld
OBJDUMP = $(CROSS)-objdump
OBJCOPY = $(CROSS)-objcopy

CFLAGS = -O2 -Wall -nostdlib -nostartfiles -ffreestanding -march=rv32imac -mabi=ilp32
LDFLAGS = -T linker.ld

SRCS = start.S kernel.c proc.c sync.c fs.c syscall.c uart.c \
       user/user_program1.c user/user_program2.c user/user_program3.c
OBJS = $(SRCS:.c=.o)
OBJS := $(OBJS:.S=.o)

all: os.elf

os.elf: $(OBJS) linker.ld
	$(CC) $(CFLAGS) $(OBJS) $(LDFLAGS) -o os.elf

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

%.o: %.S
	$(CC) $(CFLAGS) -c $< -o $@

run: os.elf
	qemu-system-riscv32 -machine virt -nographic -kernel os.elf

clean:
	rm -f $(OBJS) os.elf
