CC = gcc
CFLAGS = -Wall -Wextra
LFLAGS = -g
SOURCES = $(wildcard *.c)
EXEC = prog

all: $(EXEC)

$(EXEC) : file.o table.o
	$(CC) $(CFLAGS) -o $@ $^ $(LFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $< $(LFLAGS)

clean: 
	rm -rf *.o

