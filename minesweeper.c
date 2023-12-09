/**
 * @file minesweeper.c
 * @brief contains functions for the minesweeper game
 * 
 * Course: CPE2600
 * Section: 131
 * Assignment: Final Project
 * Name: Sydney Balboni 
 */

#include <ncurses.h>
#include <stdlib.h>
#include <unistd.h>

#include "field.h"
#include "minesweeper.h"

void print_console();
void print_leaderboard();
void menu();
void display_field(game* g);
void print_rules();
void reveal_block(game *g, int x, int y);
void mark_flag(game *g, int x, int y);
int check_game_over(game *g);

/**
 * @brief The game loop
 * 
 * @param field_size The size of the game field
 * @return int 0 if successful
*/
int minesweeper(size field_size) {
    // Setup ncurses for console printing
    initscr();  
    cbreak();  
    noecho();  
    keypad(stdscr, TRUE);
    curs_set(2); // Show the cursor as a block
    nodelay(stdscr, FALSE); // Set to FALSE to wait for user input

    game *g;

    // Initialize the game
    g = malloc(sizeof(game));
    g->score = 0;
    g->time = 0;
    g->field_size = field_size;

    make_field(g, g->field_size); // New function to initialize game

    int ch, x = 0, y = 0;
    int game_over = 0;

    mvprintw(5, 0, "%s", "Press any key to start...");

    // Game loop
    while(!game_over && (ch = getch()) != 'q') {
        display_field(g); // Display the game field

        switch(ch) {
            case KEY_UP:    y = (y > 0) ? y - 1 : y; break;
            case KEY_DOWN:  y = (y < g->field_size - 1) ? y + 1 : y; break;
            case KEY_LEFT:  x = (x > 0) ? x - 1 : x; break;
            case KEY_RIGHT: x = (x < g->field_size - 1) ? x + 1 : x; break;
            case 'f':       mark_flag(g, y, x); break;  // Mark flag
            case 'r':       reveal_block(g, y, x); break; // Reveal block
        }

        move(y + 3, x * 3 + 1); // Adjust cursor position
        refresh();  

        game_over = check_game_over(g); // Check if game is over
    }

    // Game over logic
    if (game_over == 1 || game_over == 2) {
        for (int i = 0; i < g->field_size; i++) {
            for (int j = 0; j < g->field_size; j++) {
                g->field[i][j].is_revealed = 1;
            }
        }
    }

    display_field(g);
    if (game_over == 1) {
        mvprintw(g->field_size + 6, 0, "%s", "Game over!");
    } 
    else 
    {
        mvprintw(g->field_size + 6, 0, "%s", "Congratulations! You won!");
    }
    refresh();
    sleep(6);

    // Cleanup
    endwin(); 
    free(g); 

    return 0;
}



/**
 * @brief Prints the console
 * 
 * @param g The game
*/
void display_field(game* g) {
    // Clear the screen 
    clear();

    // Loop through the field and display cells
    mvprintw(1, 0, "%s", "MINESWEEPER");
    for (int i = 3; i < g->field_size+3; i++) {
        for (int j = 2; j < g->field_size; j++) {
            mvprintw(i, j * 3, "%s", "[ ]");
        }
    }
    for (int i = 0; i < g->field_size; i++) {
        for (int j = 0; j < g->field_size; j++) {
            char display_char = ' ';
            if (g->field[i][j].is_revealed) 
            {
                display_char = (g->field[i][j].is_mine) ? '*' : ('0' + g->field[i][j].num_adjacent_mines);
            } else if (g->field[i][j].is_flagged) 
            {
                display_char = 'F';
            }
            mvprintw(i + 3, j * 3, "[%c]", display_char);
        }
        mvprintw(g->field_size + 4, 0, "%s", "Number of mines: ");
        mvprintw(g->field_size + 4, 17, "%d", g->field_size);
    }
    refresh();
}


/**
 * @brief Reveals a block and cascades if necessary
 * 
 * @param g The game
 * @param x The x coordinate of the block
 * @param y The y coordinate of the block
 * @return int 1 if game over, 0 if not
*/
void reveal_block(game *g, int x, int y) {
    // Check bounds and if already revealed
    if (x < 0 || x >= g->field_size || y < 0 || y >= g->field_size || g->field[x][y].is_revealed) {
        return;
    }

    g->field[x][y].is_revealed = 1;

    // If the revealed block is a mine, return to let the game over logic handle it
    if (g->field[x][y].is_mine) {
        return;
    }

    // Reveal adjacent blocks if no adjacent mines
    if (g->field[x][y].num_adjacent_mines == 0) {
        for (int dx = -1; dx <= 1; dx++) {
            for (int dy = -1; dy <= 1; dy++) {
                // Check to avoid revealing the current block again
                if (dx != 0 || dy != 0) {
                    reveal_block(g, x + dx, y + dy);
                }
            }
        }
    }
}



/**
 * @brief Marks a block with a flag
 * 
 * @param g The game
 * @param x The x coordinate of the block
 * @param y The y coordinate of the block
*/
void mark_flag(game *g, int x, int y) {
    if (x < 0 || x >= g->field_size || y < 0 || y >= g->field_size || g->field[x][y].is_revealed) {
        return;
    }
    g->field[x][y].is_flagged = !g->field[x][y].is_flagged;
}



/**
 * @brief Checks if the game is over
 * 
 * @param g The game
*/
int check_game_over(game *g) {
    int mines_flagged = 0, safe_blocks_revealed = 0;
    for (int i = 0; i < g->field_size; i++) {
        for (int j = 0; j < g->field_size; j++) {
            if (g->field[i][j].is_mine && g->field[i][j].is_revealed) return 1;
            if (g->field[i][j].is_mine && g->field[i][j].is_flagged) mines_flagged++;
            if (!g->field[i][j].is_mine && g->field[i][j].is_revealed) safe_blocks_revealed++;
        }
    }
    if (mines_flagged == g->field_size || safe_blocks_revealed == g->field_size * g->field_size - g->field_size) {
        return 2;
    }
    return 0;
}



/**
 * @brief Frees the game field
 * 
 * @param g The game
*/
void free_field(game* g) {
    for (int i = 0; i < g->field_size; i++) {
        free(g->field[i]);
    }
    free(g->field);
}