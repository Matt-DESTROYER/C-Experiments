#include <stdlib.h>
#include <stdio.h>

#include "maze.h"
#include "pathfindr.h"

typedef unsigned long int ulong_t;

typedef int bool;
#define true  1
#define false 0

bool streq(char*, char*);
long file_size(FILE*);

int main(int argc, char* argv[]) {
	/* input variables */
	char* input  = NULL;       // input file  (to read maze from)
	char* output = "path.txt\0"; // output file (to write path to)

	/* handle commandline arguments */
	for (int i = 1; i < argc; i++) {
		// flags
		if (argv[i][0] == '-') {
			// custom output file
			if (
				(streq(argv[i], "-o\0")) ||
				(streq(argv[i], "--output\0"))
			) {
				output = argv[i + 1];
				i++;
			}
		} else /* input file */ {
			// error if multiple input files
			if (input != NULL) {
				fprintf(stderr, "Error: multiple input files supplied ('%s' & '%s').\n", input, argv[i]);
				return EXIT_FAILURE;
			}
			input = argv[i];
		}
	}

	// error if no input file
	if (input == NULL) {
		fprintf(stderr, "Error: no input file supplied.\n");
		return EXIT_FAILURE;
	}


	/* time to read the file and parse the maze!! */

	/*
	 * File structure:
	 * <width>x<height>
	 * <maze>
	 */

	// open the input file in read binary mode
	FILE* input_file = fopen(input, "rb");
	if (input_file == NULL) {
		fprintf(stderr, "Error: failed to open input file '%s'.\n", input);
		return EXIT_FAILURE;
	}

	// get the file's size

	long int buffer_size = file_size(input_file);
	if (buffer_size <= 0) {
		fprintf(stderr, "Error: input file '%s' is empty.\n", input);
		fclose(input_file);
		return EXIT_FAILURE;
	}

	// allocate a buffer to store the file contents
	char* buffer = (char*)malloc(sizeof(char) * buffer_size);
	if (buffer == NULL) {
		fprintf(stderr, "Error: failed to allocate buffer.\n");
		fclose(input_file);
		return EXIT_FAILURE;
	}

	if (fread(buffer, sizeof(char), buffer_size, input_file) != buffer_size) {
		fprintf(stderr, "Error: reading input file '%s'.\n", input);
		fclose(input_file);
		return EXIT_FAILURE;
	}

	fclose(input_file);

	uint_t idx = 0; // index in buffer

	// get how many chars make up the width and height values
	int width_chars = 0,
		height_chars = 0;
	while (buffer[idx] != 'x') {
		width_chars++;
		idx++;
	}
	idx++;
	while (buffer[idx] != '\n') {
		height_chars++;
		idx++;
	}
	idx++;

	// read the width value
	char* width_buffer  = (char*)malloc(sizeof(char) * (width_chars + 1));
	if (width_buffer == NULL) {
		fprintf(stderr, "Error: failed to allocate width.\n");
		return EXIT_FAILURE;
	}
	for (uint_t i = 0; i < width_chars; i++) {
		width_buffer[i] = buffer[i];
	}
	width_buffer[width_chars] = '\0';
	int maze_width = atoi(width_buffer);
	free(width_buffer);

	// read the height value
	char* height_buffer = (char*)malloc(sizeof(char) * (height_chars + 1));
	if (height_buffer == NULL) {
		fprintf(stderr, "Error: failed to allocate height.\n");
		return EXIT_FAILURE;
	}
	for (uint_t i = 0; i < height_chars; i++) {
		height_buffer[i] = buffer[width_chars + i + 1];
	}
	height_buffer[height_chars] = '\0';
	int maze_height = atoi(height_buffer);
	free(height_buffer);

	// create the maze
	maze_t* maze = maze_make(maze_width, maze_height);
	if (maze == NULL) {
		fprintf(stderr, "Error: failed to allocate maze.\n");
		free(buffer);
		return EXIT_FAILURE;
	}

	// read the maze from the buffer
	uint_t size = maze->width * maze->height;
	for (uint_t i = 0; i < size; idx++) {
		if (buffer[idx] != '\n') {
			maze->data[i] = buffer[idx];
			i++;
		}
	}

	// we're done with the buffer!!
	free(buffer);

	/* find the path */

	int path_found =  maze_find_path(maze, maze);
	if (path_found != PATH_FOUND) {
		fprintf(stderr, "Error: failed to find a path.\n");
		maze_destroy(maze);
		return EXIT_FAILURE;
	}

	/* write the output to the output file */

	FILE* output_file = fopen(output, "wb");
	if (output_file == NULL) {
		fprintf(stderr, "Error: failed to open output file '%s'.\n", output);
		return EXIT_FAILURE;
	}

	size_t bytes_written;
	for (uint_t y = 0; y < maze_height; y++) {
		bytes_written = fwrite(maze->data + y * maze_width, sizeof(char), maze_width, output_file);
		if (bytes_written != maze_width) {
			fprintf(stderr, "Error: failed to write to output file '%s'.\n", output);
			fclose(output_file);
			return EXIT_FAILURE;
		}
		bytes_written = fwrite("\n", sizeof(char), 1, output_file);
		if (bytes_written != 1) {
			fprintf(stderr, "Error: failed to write to output file '%s'.\n", output);
			fclose(output_file);
			return EXIT_FAILURE;
		}
	}

	fclose(output_file);

	// we're done with the maze!!
	maze_destroy(maze);

	/* fin!!! */
	return EXIT_SUCCESS;
}

/**
 * Check if two strings are equal (returns 'true' or 'false').
 */
bool streq(char* a, char* b) {
	uint_t i = 0;
	while (true) {
		if ((a[i] == '\0') || (b[i] == '\0')) {
			return !(
				((a[i] == '\0') && (b[i] != '\0')) ||
				((a[i] != '\0') && (b[i] == '\0'))
			);
		}
		if (a[i] != b[i]) {
			return false;
		}
		i++;
	}
	return true;
}

/**
 * Find the size of a file (returns a 'long').
 */
long file_size(FILE* file) {
	if (file == NULL) return 0;

	// attempt to move to the end of the file
	if (fseek(file, 0, SEEK_END) != 0) return 0;

	// remember where the end is
	long size = (long)ftell(file);

	// go back to where we were
	rewind(file);

	// (convert the index to a size)
	return size;
}

