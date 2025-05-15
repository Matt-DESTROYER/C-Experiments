#ifndef MAZE_H
#define MAZE_H

#include <stdlib.h>
#include <stdio.h>

typedef unsigned int uint_t;

typedef struct maze {
	uint_t width;
	uint_t height;
	char* data;
} maze_t;

maze_t* maze_make(uint_t width, uint_t height);
void    maze_destroy(maze_t* maze);
void    maze_clear(maze_t* maze);
char    maze_at(maze_t* maze, uint_t x, uint_t y);
void    maze_set(maze_t* maze, char value, uint_t x, uint_t y);
void    maze_find(maze_t* maze, char value, int* x, int* y);
void    maze_print(maze_t* maze);

#define MAZE_EMPTY         ' '
#define MAZE_VISIBLY_EMPTY '.'
#define MAZE_BLOCK         '#'
#define MAZE_START         '@'
#define MAZE_END           '$'
#define MAZE_PATH          '+'
#define MAZE_VISITED       '*'

#endif

