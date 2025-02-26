#include "sort_algorithms.h"

void bubble_sort_init(void *state, int *array, size_t size, int target) {
  (void)target; // Unused
  SortState *s = (SortState *)state;
  s->array = array;
  s->size = size;
  s->pass = 0;
  s->index = 0;
  s->swapped = false;
  s->done = false;
  s->algo_id = 0;
}

bool bubble_sort_step(void *state) {
  SortState *s = (SortState *)state;
  if (s->done)
    return true;

  if (s->index < s->size - s->pass - 1) {
    if (s->array[s->index] > s->array[s->index + 1]) {
      int temp = s->array[s->index];
      s->array[s->index] = s->array[s->index + 1];
      s->array[s->index + 1] = temp;
      s->swapped = true;
    }
    s->index++;
  } else {
    if (s->swapped) {
      s->pass++;
      if (s->pass == s->size - 1) {
        s->done = true;
      } else {
        s->index = 0;
        s->swapped = false;
      }
    } else {
      s->done = true;
    }
  }
  return s->done;
}
