CC=gcc

clean:
	@rm -rf *.txt \
	@rm -rf ./main

input:
	@printf "%d\n%d" $$RANDOM $$RANDOM >> input.txt

build:
	@$(CC) -o main main.c

test_build:
	@$(CC) -fsanitize=address -o main main.c

run: clean input build
	@./main

test: clean input test_build
	ASAN_OPTIONS=detect_leaks=1 ./main
