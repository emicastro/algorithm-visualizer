#include <stdbool.h>
#include <stdlib.h>

// Enum for algorithm types
typedef enum { ALGO_SORT, ALGO_SEARCH } AlgorithmType;

// Structure to define an algorithm
typedef struct {
  const char *name;
  AlgorithmType type;
  void (*init)(void *state, int *array, size_t size, int target);
  bool (*step)(void *state);
} Algorithm;

int main(void) {}
