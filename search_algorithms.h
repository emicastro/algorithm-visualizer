#ifndef SEARCH_ALGORITHMS_H
#define SEARCH_ALGORITHMS_H

#include <stdbool.h>
#include <stddef.h>

typedef struct {
  int *array;
  size_t size;
  int target;
  bool found;
  bool done;
  int algo_id;
} SearchState;

#endif // !SEARCH_ALGORITHMS_H
