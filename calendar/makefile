CC = gcc
CFLAGS = -Wall -Wextra
LFLAGS = -g
SOURCES = $(wildcard *.c)
EXEC = prog

all: $(EXEC)

$(EXEC) : menu.o action.o semaine.o
	$(CC) $(CFLAGS) -o $@ $^ $(LFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $< $(LFLAGS)

test: test.o action.o semaine.o
	$(CC) $(CFLAGS) -o $@ $^ $(LFLAGS)	
clean: 
	rm -rf *.o

