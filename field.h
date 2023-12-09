/**
 * @file field.h
 * @brief contains the definitions and 
 * prototypes for the minesweeper field
 * 
 * Course: CPE2600
 * Section: 131
 * Assignment: Final Project
 * Name: Sydney Balboni 
 */

#ifndef FIELD_H
#define FIELD_H

#include "minesweeper.h"

// Function Prototypes
void make_field(game*, size);
void calculate_adjacent_mines(game*);

#endif 
