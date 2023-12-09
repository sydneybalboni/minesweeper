/**
 * @file main.c
 * @brief contains the main function for the minesweeper game
 * 
 * Course: CPE2600
 * Section: 131
 * Assignment: Final Project
 * Name: Sydney Balboni 
 */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "minesweeper.h"

size handle_args(int argc, char* argv[]);
void show_help();


/**
 * @brief The main function
 * 
 * @param argc The number of arguments
 * @param argv The arguments
*/
int main(int argc, char *argv[]) 
{
    size size = handle_args(argc, argv);

    minesweeper(size);
    
    return 0;
}


/**
 * @brief Handles command line arguments
 * 
 * @param argc The number of arguments
 * @param argv The arguments
 * @return size The size of the game field
*/
size handle_args(int argc, char* argv[]) {
    int opt;
    size size = MEDIUM; // Default value

    // Handle command line arguments
    while ((opt = getopt(argc, argv, "s:h")) != -1) {
        switch (opt) {
            case 's':
                if (strcmp(optarg, "small") == 0) {
                    size = SMALL;
                }
                else if (strcmp(optarg, "medium") == 0) {
                    size = MEDIUM;
                }
                else if (strcmp(optarg, "large") == 0) {
                    size = LARGE;
                }
                else if (strcmp(optarg, "x-small") == 0) {
                    size = X_SMALL;
                }
                else {
                    printf("Invalid size. Defaulting to medium.\n");
                }
                break;
            case 'h':
                show_help();
                exit(0);
                break;
            default: // In case of unknown options
                show_help();
                exit(1);
        }
    }

    return size;
}

/**
 * @brief Shows the help message
*/
void show_help()
{
    printf("\n");
    printf("Usage: minesweeper [-s size] [-h]\n");
    printf("\n");
    printf("Options:\n");
    printf("  -s size\t\tSet the size of the game field. Valid sizes are x-small, small, medium, and large.\n");
    printf("  -h\t\t\tShow this help message.\n");
    printf("\n");
    printf("Controls:\n");
    printf("  Arrow keys\t\tMove the cursor\n");
    printf("  r\t\t\tReveal a block\n");
    printf("  f\t\t\tFlag a block\n");
    printf("  q\t\t\tQuit the game\n");
    printf("\n");
    printf("Rules:\n");
    printf("  The goal of the game is to reveal all blocks that do not contain mines.\n");
    printf("  If you reveal a block with a mine, you lose.\n");
    printf("  If you reveal all blocks without mines, you win.\n");
    printf("  If you reveal a block with no adjacent mines, all adjacent blocks will be revealed.\n");
    printf("  If you reveal a block with adjacent mines, the number of adjacent mines will be displayed.\n");
    printf("  If you flag all blocks with mines, you win.\n");
    printf("\n");
}