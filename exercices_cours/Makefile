CC = arm-none-eabi-gcc
CFLAGS = -Wall -Werror -g -Og 
LDFLAGS = -L/opt/mylibs
TARGET_ARCH = -mthumb
LDLIBS = -lm
OBJS = main.o t1.o t2.o stubs.o
EXE = hello

$(EXE) : $(OBJS)
	$(LINK.o) $^ $(LDLIBS) -o $@

stubs.o : libs/stubs.c
	$(CC) -g -O2 $(TARGET_ARCH) -c -o $@ $^

clean :
	rm *.o
	rm hello

