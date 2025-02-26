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
