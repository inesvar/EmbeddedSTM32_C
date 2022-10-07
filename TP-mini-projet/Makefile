PREFIX =arm-none-eabi
CC = $(PREFIX)-gcc
LD = $(PREFIX)-ld
AS = $(PREFIX)-as
CFLAGS = -g -O1 -ffreestanding -mfloat-abi=hard -Wall -Wextra -Werror
ASFLAGS = -g -mthumb
TARGET_ARCH = -mcpu=cortex-m4 -mthumb
LDFLAGS = -T ld_ram.lds -nostdlib -g

OBJS_A = crt0.o led.o main.o
OBJS := $(OBJS_A) clocks.o
EXE = main

GDB   = gdb-multiarch

%.o:%.s
	$(AS) $(ASFLAGS) $< -o $@

%.o:%.c %.h
	$(CC) $(CFLAGS) $(TARGET_ARCH) $< -c -o $@

$(EXE):$(OBJS)
	$(CC) $(LDFLAGS) $^ -o $@


connect:
	JLinkGDBServer -device STM32L475VG -endian little -if SWD -speed auto -ir -LocalhostOnly

debug:
	$(GDB) -x se203.gdb

clean :
	rm $(OBJS_A)
	rm $(EXE)