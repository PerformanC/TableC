CC := clang

FLAGS := -I../ -std=c89 -g
FILES := special_cases.c ../tablec.c

all:
	$(CC) $(FILES) $(FLAGS) -o test
	$(CC) fuzzy_benchmarking.c ../tablec.c -I.. -std=c99 -o benchmark

clear:
	rm test
	rm benchmark