#include "utils.h"
#include <stddef.h>
#include <stdlib.h>

void generate_random_array(int *array, size_t size) {
  for (size_t i = 0; i < size; i++) {
    array[i] = rand() % 100; // Values 0-99
  }
}

void generate_sorted_array(int *array, size_t size) {
  for (size_t i = 0; i < size; i++) {
    array[i] = (int)i; // 0 to size-1
  }
}
