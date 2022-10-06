PREFIX =arm-none-eabi
CC = $(PREFIX)-gcc
CFLAGS = -ffreestanding -Wall -O1 -c
TARGET_ARCH = -mcpu=cortex-m4 -mthumb

EXE = exo3.o

%.o:%.c
	$(CC) $(CFLAGS) $(TARGET_ARCH) $< -o $@

clean :
	rm $(EXE)