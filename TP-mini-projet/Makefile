PREFIX =arm-none-eabi-
CC = $(PREFIX)gcc
LD = $(PREFIX)ld
AS = $(PREFIX)as
CFLAGS = -g -O1 -ffreestanding -Wall -Wextra -Werror 
CFLAGS += -I ../CMSIS/Device/ST/STM32L4xx/Include -I ../CMSIS/Include
ASFLAGS = -g -mthumb
TARGET_ARCH = -mcpu=cortex-m4 -mthumb -mfloat-abi=hard 
LDFLAGS = -T ld_ram.lds -nostdlib -g

OBJS_A = crt0.o matrix.o main.o init.o using_led_matrix.o irq.o uart.o
OBJS := $(OBJS_A) clocks.o
EXE = main.elf

GDB   = gdb-multiarch

%.o:%.s
	$(AS) $(ASFLAGS) $< -o $@

%.o:%.c %.h
	$(CC) $(CFLAGS) $(TARGET_ARCH) $< -c -o $@

$(EXE):$(OBJS)
	$(CC) $(LDFLAGS) $^ -o $@

image.o:image.raw
	$(PREFIX)objcopy -I binary -O elf32-littlearm -B armv7e-m $< $@

connect:
	JLinkGDBServer -device STM32L475VG -endian little -if SWD -speed auto -ir -LocalhostOnly

debug:
	$(GDB) -x se203.gdb main.elf

clean :
	rm $(OBJS_A)
	rm $(EXE)