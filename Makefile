CC=gcc
CFLAGS=-Isrc -Wall -g

TARGET=xis
EXTRA=src/memory.c src/set.c src/debug.c src/val.c src/vm.c
all: $(TARGET)

$(TARGET): $(TARGET).c
	$(CC) $(CFLAGS) -o bin/$(TARGET) $(TARGET).c $(EXTRA) 

clean:
	$(RM) $(TARGET)
