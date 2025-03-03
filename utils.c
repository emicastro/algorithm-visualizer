#include "utils.h"
#include <stddef.h>
#include <stdlib.h>

void generate_random_array(int *array, size_t size) {
  for (size_t i = 0; i < size; i++) {
    array[i] = rand() % 30; // Values 0-29 for easier visualizations
  }
}

void generate_sorted_array(int *array, size_t size) {
  for (size_t i = 0; i < size; i++) {
    array[i] = (int)i; // 0 to size-1
  }
}

int find_max(int *array, size_t size) {
  int max_val = array[0];
  for (size_t i = 1; i < size; i++) {
    if (array[i] > max_val) {
      max_val = array[i];
    }
  }
  return max_val;
}
