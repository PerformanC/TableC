CC := clang

FLAGS := -I.. -std=c89 -ggdb
FILES := ../tablec.c

all:
	$(CC) special_cases.c $(FILES) $(FLAGS) -o test
	$(CC) fuzzy_benchmarking.c $(FILES) $(FLAGS) -o benchmark

clear:
	rm test
	rm benchmark