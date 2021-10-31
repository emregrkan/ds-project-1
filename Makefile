CC=gcc

input:
	printf "%d\n%d" $$RANDOM $$RANDOM >> input.txt

build: main.c
	$(CC) -o main main.c

run: main
	./main
