#include "pathfindr.h"

bool unexplored_cell(maze_t* maze, uint_t x, uint_t y) {
	char cell = maze_at(maze, x, y);
	return (
		(cell == MAZE_EMPTY) ||
		(cell == MAZE_START) ||
		(cell == MAZE_END)
	);
}

void explore_cell(maze_t* maze, char value, uint_t x, uint_t y) {
	maze_set(maze, value, x, y);
	recurse_adjacents(maze, x, y);
}

void recurse_adjacents(maze_t* maze, uint_t x, uint_t y) {
	if ((x > 0) && (unexplored_cell(maze, x - 1, y))) {
		explore_cell(maze, PATH_RIGHT, x - 1, y);
	}
	if ((y > 0) && (unexplored_cell(maze, x, y - 1))) {
		explore_cell(maze, PATH_DOWN, x, y - 1);
	}
	if ((x < (maze->width - 1)) && (unexplored_cell(maze, x + 1, y))) {
		explore_cell(maze, PATH_LEFT, x + 1, y);
	}
	if ((y < (maze->height - 1)) && (unexplored_cell(maze, x, y + 1))) {
		explore_cell(maze, PATH_UP, x, y + 1);
	}
}

void find_path(maze_t* maze, int start_x, int start_y, int end_x, int end_y) {
	//int x_dir = end_x - start_x, y_dir = end_y - start_y;

	recurse_adjacents(maze, (uint_t)end_x, (uint_t)end_y);
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

	// trace path
	if (maze_at(output_maze, (uint_t)start_x, (uint_t)start_y) != MAZE_START) {
		uint_t curr_x = (uint_t)start_x, curr_y = (uint_t)start_y,
		       next_x = curr_x, next_y = curr_y;
		while ((curr_x != end_x) || (curr_y != end_y)) {
			next_position(output_maze, &next_x, &next_y);
			maze_set(output_maze, MAZE_PATH, curr_x, curr_y);
			curr_x = next_x;
			curr_y = next_y;
		}
	}

	for (uint_t y = 0; y < output_maze->height; y++) {
		for (uint_t x = 0; x < output_maze->width; x++) {
			switch (maze_at(output_maze, x, y)) {
				case PATH_LEFT:
				case PATH_RIGHT:
				case PATH_UP:
				case PATH_DOWN:
					maze_set(output_maze, MAZE_VISITED, x, y);
					break;
			}
		}
	}

	// cleanup
	maze_set(output_maze, MAZE_START, (uint_t)start_x, (uint_t)start_y);
	maze_set(output_maze, MAZE_END, (uint_t)end_x, (uint_t)end_y);

	printf("[OUTPUT MAZE]\n");
	maze_print(output_maze);

	return PATH_FOUND;
}

