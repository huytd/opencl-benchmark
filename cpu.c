#include <stdio.h>
#include <time.h>

typedef unsigned long long fuckin_large;

int main() {
  clock_t begin = clock();
  fuckin_large val = 0;
  for (fuckin_large j = 0; j < 100000000; j++) {
    val += j;
  }
  printf("Result: %llu\n", val);
  clock_t end = clock();
  double runtime = (double)(end - begin) / CLOCKS_PER_SEC;
  printf("Runtime: %lfms\n", runtime);
}
