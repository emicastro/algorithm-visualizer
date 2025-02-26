#include "search_algorithms.h"

void linear_search_init(void *state, int *array, size_t size, int target) {
  SearchState *s = (SearchState *)state;
  s->array = array;
  s->size = size;
  s->target = target;
  s->current_index = 0;
  s->found = false;
  s->done = (size == 0);
  s->algo_id = 0;
}

bool linear_search_step(void *state) {
  SearchState *s = (SearchState *)state;
  if (s->done)
    return true;

  if (s->array[s->current_index] == s->target) {
    s->found = true;
    s->done = true;
  } else {
    s->current_index++;
    if (s->current_index >= s->size) {
      s->done = true;
    }
  }
  return s->done;
}

void binary_search_init(void *state, int *array, size_t size, int target) {
  SearchState *s = (SearchState *)state;
  s->array = array;
  s->size = size;
  s->target = target;
  s->low = 0;
  s->high = size - 1;
  s->found = false;
  s->done = (size == 0);
  s->algo_id = 1;
}

bool binary_search_step(void *state) {
  SearchState *s = (SearchState *)state;
  if (s->done)
    return true;

  if (s->low > s->high) {
    s->done = true;
  } else {
    s->current_index = s->low + (s->high - s->low) / 2;
    if (s->array[s->current_index] == s->target) {
      s->found = true;
      s->done = true;
    } else if (s->array[s->current_index] < s->target) {
      s->low = s->current_index + 1;
    } else {
      s->high = s->current_index - 1;
    }
  }
  return s->done;
}
