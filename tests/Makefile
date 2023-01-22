CC := clang

FLAGS := -I.. -std=c89 -ggdb
FILES := ../tablec.c

all:
	$(CC) fuzzy_benchmarking.c $(FILES) $(FLAGS) -o benchmark
	$(CC) special_cases.c $(FILES) $(FLAGS) -o test

clear:
	rm test
	rm benchmark