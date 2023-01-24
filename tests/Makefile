CC := clang

FLAGS := -I.. -std=c89 -ggdb -Wall -Wextra -Wpedantic
FILES := ../tablec.c

all:
	$(CC) ../tablec.c -std=c89 -fPIC -c -o ../tablec.o -Wall -Wextra -Wpedantic
	rm ../tablec.o
	$(CC) benchmarking.c $(FILES) $(FLAGS) -o benchmark
	$(CC) testing.c $(FILES) $(FLAGS) -o test

clear:
	rm test
	rm benchmark