CC = gcc
CFLAGS = -Wall -Wextra

all: logo_interpreter

logo_interpreter: main.o lexer.o parser.o execute.o
	$(CC) $(CFLAGS) -o logo_interpreter main.o lexer.o parser.o execute.o

main.o: main.c lexer.h parser.h execute.h
	$(CC) $(CFLAGS) -c main.c

lexer.o: lexer.c lexer.h
	$(CC) $(CFLAGS) -c lexer.c

parser.o: parser.c parser.h lexer.h
	$(CC) $(CFLAGS) -c parser.c

execute.o: execute.c execute.h parser.h
	$(CC) $(CFLAGS) -c execute.c

clean:
	rm -f *.o logo_interpreter
