#ifndef SORT_ALGORITHMS_H
#define SORT_ALGORITHMS_H

#include <stdbool.h>
#include <stddef.h>

typedef struct {
  int *array;
  size_t size;
  size_t pass;    // Used by Bubble Sort
  size_t index;   // Current index
  size_t key_pos; // Used by Insertion Sort
  int key;        // Used by Insertion Sort
  bool swapped;   // Used by Bubble Sort
  bool done;
  int algo_id; // 0 for Bubble Sort
} SortState;

void bubble_sort_init(void *state, int *array, size_t size, int target);
bool bubble_sort_step(void *state);
void insertion_sort_init(void *state, int *array, size_t size, int target);
bool insertion_sort_step(void *state);

#endif
