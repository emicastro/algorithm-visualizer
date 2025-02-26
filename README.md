# Algorithm Visualazer

## How It Works
#### Startup: The program initializes ncurses and displays a menu listing the four algorithms.
#### Navigation: Use UP/DOWN keys to select an algorithm, +/- to adjust speed (minimum 10ms).
#### Run Mode ('r'):
- Generates a random array for sorting or a sorted array for searching.
- Runs the visualization automatically with the selected speed.
- Press 's' to stop early.
- Returns to the menu after completion or interruption.
#### Step Mode ('t'):
- Same array generation as run mode.
- Advances one step per 't' press.
- Press 'q' to return to the menu.

### Visualization:
#### Sorting: Highlights current indices (red).
#### Searching: Highlights current index (and range bounds for Binary Search).
Quit: Press 'q' from the menu to exit.

### Extensibility
To add a new algorithm:

- Define its init and step functions in sort_algorithms.c or search_algorithms.c (or a new file).
- Update the corresponding header.
- Add an entry to the algorithms array in main.c with its type and function pointers.

### Notes
- C23 Compliance: The code uses C11 features (e.g., stdbool.h, size_t), which are compatible with C23. C23-specific features like nullptr are avoided for compatibility with ncurses.
- Simplifications: Array size is fixed at 20, and searching uses sorted arrays with a guaranteed target for demonstration purposes.
