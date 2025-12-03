CROSS = riscv64-unknown-elf
CC    = $(CROSS)-gcc

CFLAGS = -O2 -Wall -nostdlib -nostartfiles -ffreestanding \
         -march=rv64imac -mabi=lp64
LDFLAGS = -T linker.ld

SRCS = start.S kernel.c proc.c sync.c fs.c syscall.c uart.c \
       user/user_program1.c user/user_program2.c user/user_program3.c
OBJS = $(SRCS:.c=.o)
OBJS := $(OBJS:.S=.o)

all: os.elf

os.elf: $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LDFLAGS) -o os.elf

run: os.elf
	qemu-system-riscv64 -machine virt -nographic -kernel os.elf

clean:
	rm -f $(OBJS) os.elf
