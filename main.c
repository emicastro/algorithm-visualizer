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

// List of available algorithms
Algorithm algorithms[] = {

};

const size_t num_algorithms = sizeof(algorithms) / sizeof(algorithms[0]);

// State variables
void *current_state;

// Global variables
size_t selected_algo = 0; // Currently selected algorithm index
int speed = 100;          // Visualization speed in milliseconds
#define ARRAY_SIZE 20     // Fixed array size for simplicity
int array[ARRAY_SIZE];    // Array to visualize
int target;               // Target value for searching

// Function prototypes
void draw_menu(void);
void draw_visualization(void);
void run_visualization(void);
void step_visualization(void);

int main(void) {}
