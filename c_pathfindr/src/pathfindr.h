#ifndef PATHFINDR_H
#define PATHFINDR_H

#include "maze.h"

#define PATH_FOUND 0
#define PATH_NOT_FOUND -1

#define PATH_UP    'U'
#define PATH_DOWN  'D'
#define PATH_LEFT  'L'
#define PATH_RIGHT 'R'

int maze_find_path(maze_t* input_maze, maze_t* output_maze);

#endif

