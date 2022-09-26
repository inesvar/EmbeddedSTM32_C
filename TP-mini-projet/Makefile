PREFIX =arm-none-eabi
CC = $(PREFIX)-gcc
LD = $(PREFIX)-ld
CFLAGS = -g -O1
TARGET_ARCH = -mcpu=cortex-m4 -mthumb
LDFLAGS = -T ld_ram.lds 

GDB   = gdb-multiarch

main.o:main.c
	$(CC) -c $(CFLAGS) $(TARGET_ARCH) $^ -o $@
#  COMPILE.c = $(CC) $(CFLAGS) $(CPPFLAGS) $(TARGET_ARCH) -c

main:main.o
	$(LD) $(LDFLAGS) $^ -o $@

connect:
	JLinkGDBServer -device STM32L475VG -endian little -if SWD -speed auto -ir -LocalhostOnly

debug:
	$(GDB) -x se203.gdb