#include "pathfindr.h"
/*
void adjacent_directions(maze_t* maze, uint_t x, uint_t y) {
	// left cell
	if ((x > 0) && (maze_at(maze, x - 1, y) != MAZE_BLOCK)) {
		maze_set(maze, PATH_RIGHT, x - 1, y);
	}
	// right cell
	if ((x < (maze->width - 1)) && (maze_at(maze, x + 1, y) != MAZE_BLOCK)) {
		maze_set(maze, PATH_LEFT, x + 1, y);
	}
	// top cell
	if ((y > 0) && (maze_at(maze, x, y - 1) != MAZE_BLOCK)) {
		maze_set(maze, PATH_DOWN, x, y - 1);
	}
	// bottom cell
	if ((y < (maze->height - 1)) && (maze_at(maze, x, y + 1) != MAZE_BLOCK)) {
		maze_set(maze, PATH_UP, x, y + 1);
	}
}
*/
void recurse_adjacents(maze_t* maze, uint_t x, uint_t y, int x_dir, int y_dir) {
	if (x_dir > 0) {
		if ((x > 0) && (maze_at(maze, x - 1, y) != MAZE_BLOCK)) {
			maze_set(maze, PATH_RIGHT, x - 1, y);
			recurse_adjacents(maze, x - 1, y, x_dir, y_dir);
		}
		if ((x < (maze->width - 1)) && (maze_at(maze, x + 1, y) != MAZE_BLOCK)) {
			maze_set(maze, PATH_LEFT, x + 1, y);
			recurse_adjacents(maze, x + 1, y, x_dir, y_dir);
		}
	} else {
		if ((x < (maze->width - 1)) && (maze_at(maze, x + 1, y) != MAZE_BLOCK)) {
			maze_set(maze, PATH_LEFT, x + 1, y);
			recurse_adjacents(maze, x + 1, y, x_dir, y_dir);
		}
		if ((x > 0) && (maze_at(maze, x - 1, y) != MAZE_BLOCK)) {
			maze_set(maze, PATH_RIGHT, x - 1, y);
			recurse_adjacents(maze, x - 1, y, x_dir, y_dir);
		}
	}
	if (y_dir > 0) {
		if ((y > 0) && (maze_at(maze, x, y - 1) != MAZE_BLOCK)) {
			maze_set(maze, PATH_DOWN, x, y - 1);
			recurse_adjacents(maze, x, y - 1, x_dir, y_dir);
		}
		if ((y < (maze->height - 1)) && (maze_at(maze, x, y + 1) != MAZE_BLOCK)) {
			maze_set(maze, PATH_UP, x, y + 1);
			recurse_adjacents(maze, x, y + 1, x_dir, y_dir);
		}
	} else {
		if ((y < (maze->height - 1)) && (maze_at(maze, x, y + 1) != MAZE_BLOCK)) {
			maze_set(maze, PATH_UP, x, y + 1);
			recurse_adjacents(maze, x, y + 1, x_dir, y_dir);
		}
		if ((y > 0) && (maze_at(maze, x, y - 1) != MAZE_BLOCK)) {
			maze_set(maze, PATH_DOWN, x, y - 1);
			recurse_adjacents(maze, x, y - 1, x_dir, y_dir);
		}
	}
}

void find_path(maze_t* maze, int start_x, int start_y, int end_x, int end_y) {
	int x_dir = end_x - start_x,
		y_dir = end_y - start_y;

	recurse_adjacents(maze, (uint_t)end_x, (uint_t)end_y, x_dir, y_dir);
}

void next_position(maze_t* maze, uint_t* x, uint_t* y) {
	switch (maze_at(maze, *x, *y)) {
		case PATH_LEFT:
			(*x)--;
			break;
		case PATH_RIGHT:
			(*x)++;
			break;
		case PATH_UP:
			(*y)--;
			break;
		case PATH_DOWN:
			(*y)++;
			break;
	}
}

int maze_find_path(maze_t* input_maze, maze_t* output_maze) {
	// locate the start and end positions
	int start_x, start_y,
		end_x, end_y;

	maze_find(input_maze, MAZE_START, &start_x, &start_y);
	maze_find(input_maze, MAZE_END, &end_x, &end_y);

	if (
			((start_x == -1) && (start_y == -1)) ||
			((end_x == -1)   && (end_y == -1))
	) {
		return PATH_NOT_FOUND;
	}

	// find a path
	find_path(output_maze, start_x, start_y, end_x, end_y);

	maze_print(output_maze);

	// trace path
	uint_t x = (uint_t)start_x, y = (uint_t)start_y;
	next_position(output_maze, &x, &y);
	while ((x != end_x) && (y != end_y)) {
		maze_set(output_maze, MAZE_PATH, x, y);
		next_position(output_maze, &x, &y);
		maze_print(output_maze);
	}

	for (uint_t y = 0; y < output_maze->height; y++) {
		for (uint_t x = 0; x < output_maze->width; x++) {
			switch (maze_at(output_maze, x, y)) {
				case PATH_LEFT:
				case PATH_RIGHT:
				case PATH_UP:
				case PATH_DOWN:
					maze_set(output_maze, MAZE_EMPTY, x, y);
					break;
			}
		}
	}

	printf("[OUTPUT MAZE]\n");
	maze_print(output_maze);

	return PATH_FOUND;
}

