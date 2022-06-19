CC = gcc
CFLAGS = -Wall -Wextra
LFLAGS = -g
SOURCES = $(wildcard *.c)
EXEC = inversion

all: $(EXEC)

$(EXEC) : inversion.o struct.o file.o pile.o
	$(CC) $(CFLAGS) -o $@ $^ $(LFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $< $(LFLAGS)

clean: 
	rm -rf *.o

