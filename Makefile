CC=gcc

clean:
	@rm -rf *.txt

input:
	@printf "%d\n%d" $$RANDOM $$RANDOM >> input.txt

build:
	@$(CC) -o main main.c

run: clean input build
	@./main
