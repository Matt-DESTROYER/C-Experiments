#include "maze.h"

maze_t* maze_make(uint_t width, uint_t height) {
	maze_t* maze = (maze_t*)malloc(sizeof(maze_t));
	if (maze == NULL) {
		return NULL;
	}

	maze->width  = width;
	maze->height = height;

	uint_t size  = width * height;
	maze->data   = (char*)malloc(sizeof(char) * size);
	if (maze->data == NULL) {
		free(maze);
		return NULL;
	}

	for (uint_t i = 0; i < size; i++) {
		maze->data[i] = MAZE_EMPTY;
	}

	return maze;
}

void maze_destroy(maze_t* maze) {
	free(maze->data);
	free(maze);
}

void maze_clear(maze_t* maze) {
	uint_t size = maze->width * maze->height;
	for (uint_t i = 0; i < size; i++) {
		maze->data[i] = MAZE_EMPTY;
	}
}

char maze_at(maze_t* maze, uint_t x, uint_t y) {
	return maze->data[(y * maze->width) + x];
}

void maze_set(maze_t* maze, char value, uint_t x, uint_t y) {
	maze->data[(y * maze->width) + x] = value;
}

void maze_find(maze_t* maze, char value, int* x_out, int* y_out) {
	for (uint_t y = 0; y < maze->height; y++) {
		for (uint_t x = 0; x < maze->width; x++) {
			if (maze_at(maze, x, y) == value) {
				(*x_out) = (int)x;
				(*y_out) = (int)y;
				return;
			}
		}
	}
	(*x_out) = -1;
	(*y_out) = -1;
}

void maze_print(maze_t* maze) {
	for (uint_t y = 0; y < maze->height; y++) {
		for (uint_t x = 0; x < maze->width; x++) {
			char cell = maze_at(maze, x, y);
			if (cell == MAZE_EMPTY) {
				putchar(MAZE_VISIBLY_EMPTY);
			} else {
				putchar(cell);
			}
		}
		putchar('\n');
	}
}

