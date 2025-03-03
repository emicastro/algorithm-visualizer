#include "search_algorithms.h"
#include "sort_algorithms.h"
#include "utils.h"
#include <locale.h>
#include <ncurses.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <wchar.h>

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
    {"BubbleSort", ALGO_SORT, bubble_sort_init, bubble_sort_step},
    {"InsertionSort", ALGO_SORT, insertion_sort_init, insertion_sort_step},
    {"Linear Search", ALGO_SEARCH, linear_search_init, linear_search_step},
    {"Binary Search", ALGO_SEARCH, binary_search_init, binary_search_step},
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
void draw_sort_bars(const SortState *state);
void draw_search_state(const SearchState *state);
void draw_visualization(void);
void run_visualization(void);
void step_visualization(void);
void print_array(void);

int main(void) {
  setlocale(LC_CTYPE, "");
  // Initialize ncurses
  initscr();
  start_color();
  init_pair(1, COLOR_RED, COLOR_BLACK);   // For highlighting
  init_pair(2, COLOR_GREEN, COLOR_BLACK); // For found target
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
    case 'k':
      if (selected_algo > 0)
        selected_algo--;
      break;
    case KEY_DOWN:
    case 'j':
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
  printw("Controls: UP/DOWN or k/j to select, +/- to adjust speed\n");
  printw("r: run, t: step, q: quit\n");
  refresh();
}

void draw_sort_bars(const SortState *state) {
  printw("Sorting: ");
  print_array();
  printw("state->size: %d\n", state->size);
  int max_val = find_max(state->array, state->size);
  int max_height = max_val; // Maximum bar height
  printw("\n");
  for (int row = max_height; row >= 1; row--) {
    printw("    ");
    for (size_t i = 0; i < state->size; i++) {
      bool highlight =
          (state->algo_id == 0 &&
           (i == state->index || i == state->index + 1)) ||
          (state->algo_id == 1 && (i == state->key_pos || i == state->index));

      wchar_t ch = (state->array[i] >= (row * max_val / max_height))
                       ? (highlight ? 0x25A4 : 0x2588)
                       : ' ';
      printw("%lc ", ch);
    }
    printw(" %d", row);
    printw("\n");
  }
  printw("\nSteps: %zu\n", state->steps);
}

void draw_search_state(const SearchState *state) {
  printw("Searching for %d:\n", state->target);
  for (size_t i = 0; i < state->size; i++) {
    if (state->found && i == state->current_index) {
      attron(COLOR_PAIR(2)); // Green for found
    } else if (i == state->current_index ||
               (state->algo_id == 1 && (i == state->low || i == state->high))) {
      attron(COLOR_PAIR(1)); // Red for current or bounds
    }
    printw("%2d ", state->array[i]);
    if (state->found && i == state->current_index) {
      attroff(COLOR_PAIR(2));
    } else {
      attroff(COLOR_PAIR(1));
    }
  }
  if (state->found) {
    printw("\nFound at index %zu\n", state->current_index);
  } else if (state->done) {
    printw("\nNot found\n");
  }
  printw("\nSteps: %zu\n", state->steps);
}

void draw_visualization(void) {
  clear();
  if (algorithms[selected_algo].type == ALGO_SORT) {
    draw_sort_bars(&sort_state);
  } else {
    draw_search_state(&search_state);
  }
  refresh();
}

void run_visualization(void) {
  bool done = false;
  while (!done) {
    done = algorithms[selected_algo].step(current_state);
    draw_visualization();
    timeout(speed);
    int ch = getch();
    if (ch == 's')
      break;
  }
  printw("\nFinished. Press any key to continue.");
  timeout(-1); // Blocking
  getch();
}

void step_visualization(void) {
  bool done = false;
  while (!done) {
    draw_visualization();
    printw("\nPress 't' to step, 'q' to return.");
    int ch = getch();
    if (ch == 't') {
      done = algorithms[selected_algo].step(current_state);
    } else if (ch == 'q') {
      break;
    }
  }
}

void print_array(void) {
  for (size_t i = 0; i < (sizeof array / sizeof array[0]); i++) {
    printw("%d ", array[i]);
  }
  printw("\n");
}
