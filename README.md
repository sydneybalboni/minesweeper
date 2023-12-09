# Minesweeper Console Game
## By Sydney Balboni

This Minesweeper project is a custom implementation of the classic Minesweeper game, written in C and using the ncurses library for handling input and rendering the game in a terminal interface. 

## Features

- **Dynamic Field Size**: Players can choose different field sizes (small, medium, large).
- **Randomized Mine Placement**: Each game has mines randomly placed, ensuring a unique experience each time.
- **ncurses Interface**: Utilizes the ncurses library for handling user input and rendering the game in a console-based interface.
- **Game States**: Includes game over logic to handle win/loss scenarios.

## Implementation

### Structure

The project consists of multiple components:

- `main.c`: The entry point of the application.
- `field.h` and `field.c`: Define the field and related operations.
- `minesweeper.h` and `minesweeper.c`: Contain the main game logic and ncurses interface handling.

### Core Functions

- `make_field(game* g, size s)`: Initializes the game field with a given size, allocates memory for the field, and places mines randomly.
- `calculate_adjacent_mines(game* g)`: Calculates the number of mines adjacent to each cell.
- `reveal_block(game* g, int x, int y)`: Reveals a block and recursively reveals adjacent blocks if they have no adjacent mines.
- `mark_flag(game *g, int x, int y)`: Toggles a flag on a cell to mark a suspected mine.
- `check_game_over(game *g)`: Checks whether the game is over due to a mine being revealed or all safe blocks being revealed.

## Usage

Run with: `minesweeper [-s size] [-h]`

### Options:
  - `-s size`  -  Set the size of the game field. Valid sizes are x-small, small, medium, and large.
  - `-h` -  Show a help message

### Controls:
  - Arrow keys        -    Move the cursor
  - 'r'                   -  Reveal a block
  - 'f'                   -  Flag a block
  - 'q'                   -  Quit the game

### Rules:
  The goal of the game is to reveal all blocks that do not contain mines.
  If you reveal a block with a mine, you lose.
  If you reveal all blocks without mines, you win.
  If you reveal a block with no adjacent mines, all adjacent blocks will be revealed.
  If you reveal a block with adjacent mines, the number of adjacent mines will be displayed.
  If you flag all blocks with mines, you win.

