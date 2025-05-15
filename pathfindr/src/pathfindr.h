#ifndef PATHFINDR_H
#define PATHFINDR_H

#include "maze.h"

#define PATH_FOUND 0
#define PATH_NOT_FOUND -1

#define PATH_UP    'U'
#define PATH_DOWN  'D'
#define PATH_LEFT  'L'
#define PATH_RIGHT 'R'

typedef int bool;
#define true 1
#define false 0

bool unexplored_cell(maze_t* maze, uint_t x, uint_t y);
void explore_cell(maze_t* maze, char value, uint_t x, uint_t y);
void recurse_adjacents(maze_t* maze, uint_t x, uint_t y);
void find_path(maze_t* maze, int start_x, int start_y, int end_x, int end_y);
void next_position(maze_t* maze, uint_t* x, uint_t* y);
int maze_find_path(maze_t* input_maze, maze_t* output_maze);

#endif

