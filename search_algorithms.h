#ifndef SEARCH_ALGORITHMS_H
#define SEARCH_ALGORITHMS_H

#include <stdbool.h>
#include <stddef.h>

typedef struct {
  int *array;
  size_t size;
  int target;
  size_t current_index; // Used by Linear Search and as 'mid' in Binary Search
  size_t low;           // Used by Binary Search
  size_t high;          // Used by Binary Search
  bool found;
  bool done;
  int algo_id;
  size_t steps; // Step counter
} SearchState;

void linear_search_init(void *state, int *array, size_t size, int target);
bool linear_search_step(void *state);
void binary_search_init(void *state, int *array, size_t size, int target);
bool binary_search_step(void *state);

#endif // !SEARCH_ALGORITHMS_H
