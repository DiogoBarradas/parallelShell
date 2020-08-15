# Makefile for par-shell, version 1
# Sistemas Operativos, DEI/IST/ULisboa 2015-16

GROUP_NUM=81
EXERCISE_NUM=5
ARCHIVE_NAME=G$(GROUP_NUM)_E$(EXERCISE_NUM).zip
CFLAGS=-g -Wall -pedantic -std=c99

all: par-shell fibonacci div0 par-shell-terminal

coisas.o: coisas.c coisas.h
	gcc $(CFLAGS) -c coisas.c

par-shell: par-shell.o commandlinereader.o list.o coisas.o
	gcc -o par-shell par-shell.o commandlinereader.o list.o coisas.o  -pthread

commandlinereader.o: commandlinereader.c commandlinereader.h
	gcc $(CFLAGS) -c commandlinereader.c

par-shell.o: par-shell.c
	gcc $(CFLAGS) -c par-shell.c
	
list.o: list.c list.h
	gcc $(CFLAGS) -c list.c

fibonacci: fibonacci.c
	gcc $(CFLAGS) -o fibonacci fibonacci.c

par-shell-terminal: par-shell-terminal.o commandlinereader.o list.o coisas.o
	gcc -o par-shell-terminal par-shell-terminal.o commandlinereader.o list.o coisas.o  

par-shell-terminal.o: par-shell-terminal.c commandlinereader.h list.h coisas.h
	gcc $(CFLAGS) -c par-shell-terminal.c

div0: div.c
	gcc $(CFLAGS) -o div0 div.c

clean:
	rm -f *.o *.txt par-shell fibonacci div0 core $(ARCHIVE_NAME)

dist:
	zip $(ARCHIVE_NAME) *.c *.h Makefile
