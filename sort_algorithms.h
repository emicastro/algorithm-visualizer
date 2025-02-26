#ifndef SORT_ALGORITHMS_H
#define SORT_ALGORITHMS_H

#include <stdbool.h>
#include <stddef.h>

typedef struct {
  int *array;
  size_t size;
  bool done;
  int algo_id;
} SortState;

#endif
