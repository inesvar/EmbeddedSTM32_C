PREFIX =arm-none-eabi
CC = $(PREFIX)-gcc
LD = $(PREFIX)-ld
AS = $(PREFIX)-as
CFLAGS = -c -g -O1
ASFLAGS = -g -mthumb
TARGET_ARCH = -mcpu=cortex-m4 -mthumb
LDFLAGS = -T ld_ram.lds -nostdlib -g

GDB   = gdb-multiarch

crt0.o:crt0.s
	$(AS) $(ASFLAGS) $< -o $@

main.o:main.c
	$(CC) $(CFLAGS) $(TARGET_ARCH) $^ -o $@

main:crt0.o main.o
	$(CC) $(LDFLAGS) $^ -o $@


connect:
	JLinkGDBServer -device STM32L475VG -endian little -if SWD -speed auto -ir -LocalhostOnly

debug:
	$(GDB) -x se203.gdb