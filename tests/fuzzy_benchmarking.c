/*
  This benchmark is used by TableC for fuzzing testing, and also testing of the functions.
  Also for testing performance of the library. Remember that this benchmark is NOT manipulated, and all values are real, 
  .. but they can change depending of the background apps, and from your hardware.
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>

#include "../tablec.h"

#define MAX_EXECUTE 1000
#define ADD_TIMES 100000

char *Benchmarking[] = { "TableC" };

double firstBench() {
  clock_t startTime = clock();

  struct hashtable tablec;
  tablec_init(&tablec, ADD_TIMES, 1);

  char key[100];
  char *value = "Benchmarking";

  for (double i = 0;i < ADD_TIMES;i++) {
    snprintf(key, sizeof(key), "%f", i);
    tablec_set(&tablec, key, 0, value);
    char *abc = NULL;
    abc = tablec_get(&tablec, key, 0);
    tablec_del(&tablec, key, 0);
  }

  tablec_cleanup(&tablec);

  return ((double)(clock() - startTime) / CLOCKS_PER_SEC);
}

int main() {
  double executedTimes = 0;
  double addedTime = 0;

  firstBenchGoto:

  addedTime += firstBench();

  executedTimes++;

  if (executedTimes == MAX_EXECUTE) {
    printf(
      "BENCHMARK FOR: %s\n"
      "EXECUTION TIME FOR FIRST BENCH:\n"
      "  MEDIUM -> %f\n"
      " SAMPLES -> %d\n",
      Benchmarking[0], addedTime / MAX_EXECUTE, MAX_EXECUTE);
  } else {
    goto firstBenchGoto;
  }

  return 0;
}