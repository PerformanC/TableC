CC := clang

FLAGS := -I.. -std=c89 -ggdb -Wall -Wextra -Wpedantic

all:
	$(CC) benchmarking.c $(FLAGS) -o benchmark -gdwarf-4
	$(CC) testing.c $(FLAGS) -o test

clear:
	rm test
	rm benchmark