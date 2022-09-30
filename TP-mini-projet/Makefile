PREFIX =arm-none-eabi
CC = $(PREFIX)-gcc
LD = $(PREFIX)-ld
AS = $(PREFIX)-as
CFLAGS = -c -g -O1 -ffreestanding
ASFLAGS = -g -mthumb
TARGET_ARCH = -mcpu=cortex-m4 -mthumb
LDFLAGS = -T ld_ram.lds -nostdlib -g

OBJS = crt0.o init.o main.o 
EXE = main

GDB   = gdb-multiarch

%.o:%.s
	$(AS) $(ASFLAGS) $< -o $@

%.o:%.c
	$(CC) $(CFLAGS) $(TARGET_ARCH) $^ -o $@

$(EXE):$(OBJS)
	$(CC) $(LDFLAGS) $^ -o $@


connect:
	JLinkGDBServer -device STM32L475VG -endian little -if SWD -speed auto -ir -LocalhostOnly

debug:
	$(GDB) -x se203.gdb