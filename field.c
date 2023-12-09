/**
 * @file field.c
 * @brief contains the funtions for the minesweeper field
 * 
 * Course: CPE2600
 * Section: 131
 * Assignment: Final Project
 * Name: Sydney Balboni 
 */

#include <stdlib.h>
#include <time.h>

#include "field.h"
#include "minesweeper.h"


/**
 * @brief Initializes the game field
 * 
 * @param g The game struct
 * @param s The size of the game field
 */
void make_field(game* g, size s) {

    // Initialize random seed
    srand(time(NULL));

    g->field = malloc(s * sizeof(block*));
    for (int i = 0; i < s; i++) {
        g->field[i] = malloc(s * sizeof(block));
        for (int j = 0; j < s; j++) {
            g->field[i][j] = (block){0, 0, 0, 0};
        }
    }

    // Improved mine placement
    int num_mines = g->field_size;
    for (int i = 0; i < num_mines; i++) {
        while (1) {
            int x = rand() % s, y = rand() % s;
            if (!g->field[x][y].is_mine) {
                g->field[x][y].is_mine = 1;
                break;
            }
        }
    }

    // Calculate adjacent mines
    calculate_adjacent_mines(g);
}



/**
 * @brief Calculates the number of adjacent mines for each block
 * 
 * @param g The game struct
*/
void calculate_adjacent_mines(game* g) {
    for (int i = 0; i < g->field_size; i++) {
        for (int j = 0; j < g->field_size; j++) {
            if (!g->field[i][j].is_mine) continue;
            for (int dx = -1; dx <= 1; dx++) {
                for (int dy = -1; dy <= 1; dy++) {
                    int nx = i + dx, ny = j + dy;
                    if (nx >= 0 && nx < g->field_size && ny >= 0 && ny < g->field_size && !g->field[nx][ny].is_mine) {
                        g->field[nx][ny].num_adjacent_mines++;
                    }
                }
            }
        }
    }
}
