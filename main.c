#include "search_algorithms.h"
#include "sort_algorithms.h"
#include "utils.h"
#include <ncurses.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

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
SortState sort_state;
SearchState search_state;
void *current_state;

// Global variables
size_t selected_algo = 0; // Currently selected algorithm index
int speed = 100;          // Visualization speed in milliseconds
#define ARRAY_SIZE 20     // Fixed array size for simplicity
int array[ARRAY_SIZE];    // Array to visualize
int target;               // Target value for searching

// Function prototypes
void draw_menu(void);
void draw_sort_state(const SortState *state);
void draw_search_state(const SearchState *state);
void draw_visualization(void);
void run_visualization(void);
void step_visualization(void);

int main(void) {
  // Initialize ncurses
  initscr();
  start_color();
  init_pair(1, COLOR_RED, COLOR_BLACK); // For highlighting
  cbreak();
  noecho();
  keypad(stdscr, TRUE);

  // Seed random number generator
  srand((unsigned)time(NULL));

  bool quit = false;
  while (!quit) {
    draw_menu();
    int ch = getch();
    switch (ch) {
    case 'q':
      quit = true;
      break;
    case KEY_UP:
      if (selected_algo > 0)
        selected_algo--;
      break;
    case KEY_DOWN:
      if (selected_algo < num_algorithms - 1)
        selected_algo++;
      break;
    case '+':
      speed += 10;
      break;
    case '-':
      if (speed > 10)
        speed -= 10;
      break;
    case 'r':
      // Prepare array and state
      if (algorithms[selected_algo].type == ALGO_SORT) {
        generate_random_array(array, ARRAY_SIZE);
        current_state = &sort_state;
      } else {
        generate_sorted_array(array, ARRAY_SIZE);
        target = array[rand() % ARRAY_SIZE];
        current_state = &search_state;
      }
      algorithms[selected_algo].init(current_state, array, ARRAY_SIZE, target);
      run_visualization();
      break;
    case 't':
      if (algorithms[selected_algo].type == ALGO_SORT) {
        generate_random_array(array, ARRAY_SIZE);
        current_state = &sort_state;
      } else {
        generate_sorted_array(array, ARRAY_SIZE);
        target = array[rand() % ARRAY_SIZE];
        current_state = &search_state;
      }
      algorithms[selected_algo].init(current_state, array, ARRAY_SIZE, target);
      step_visualization();
      break;
    }
  }

  endwin();
  return 0;
};

void draw_menu(void) {
  clear();
  printw("Select Algorithm:\n");
  for (size_t i = 0; i < num_algorithms; i++) {
    if (i == selected_algo) {
      attron(A_REVERSE);
    }
    printw("%zu. %s\n", i + 1, algorithms[i].name);
    attroff(A_REVERSE);
  }
  printw("\nSpeed: %d ms\n", speed);
  printw("Controls: UP/DOWN to select, +/- to adjust speed\n");
  printw("r: run, t: step, q: quit\n");
  refresh();
}

void draw_sort_state(const SortState *state) {
  printw("Sorting:\n");
  for (size_t i = 0; i < state->size; i++) {
    if (i == state->index || (state->algo_id == 0 && i == state->index + 1)) {
      attron(COLOR_PAIR(1));
    }
    printw("%2d ", state->array[i]);
    attroff(COLOR_PAIR(1));
  }
  printw("\n");
}

void draw_search_state(const SearchState *state) {
  printw("Searching for %d:\n", state->target);
  for (size_t i = 0; i < state->size; i++) {
    if (i == state->current_index ||
        (state->algo_id == 1 && (i == state->low || i == state->high))) {
      attron(COLOR_PAIR(1));
    }
    printw("%2d ", state->array[i]);
    attroff(COLOR_PAIR(1));
  }
  if (state->found) {
    printw("\nFound at index %zu\n", state->current_index);
  } else if (state->done) {
    printw("\nNot found\n");
  }
}
