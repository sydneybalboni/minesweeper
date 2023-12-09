/**
 * @file minesweeper.h
 * @brief contains definitions and prototypes for the minesweeper game
 * 
 * Course: CPE2600
 * Section: 131
 * Assignment: Final Project
 * Name: Sydney Balboni 
 */

#include "field.h"

#ifndef MINESWEEPER_H
#define MINESWEEPER_H 

// Function Prototypes
int minesweeper();

// Size enum
typedef enum
{
    X_SMALL = 3, // 9
    SMALL = 5, // 25 
    MEDIUM = 8, // 64
    LARGE = 12 // 144
} size;


typedef struct 
{
    int is_mine;
    int is_flagged;
    int is_revealed;
    int num_adjacent_mines;
} block;

// Game struct
typedef struct 
{
    unsigned int score;
    unsigned int time;
    block **field;  // 2D array of blocks
    size field_size;
} game;

#endif