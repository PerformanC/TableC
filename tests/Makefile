CC := clang

FLAGS := -I.. -std=c89 -g
FILES := special_cases.c ../tablec.c

all:
	$(CC) -c ../tablec.c $(FLAGS) -fpic -Wall -Wextra -Wpedantic
	ar qv libtablec.a *.o
	rm *.o
	rm *.a
	$(CC) $(FILES) $(FLAGS) -o test
	$(CC) fuzzy_benchmarking.c ../tablec.c -I.. -std=c89 -o benchmark

clear:
	rm test
	rm benchmark