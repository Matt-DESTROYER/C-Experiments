#include <stdlib.h>
#include <stdio.h>

#include "dynamic_array.h"

/**
 * dynamic_array_t* make_dynamic_arr(size_t length, size_t size);
 *
 * Properly initializes a dynamic_array_t structure with a given `length` of elements
 * and a give `size` of each individual element (eg `sizeof(int)`).
 */
LIB_EXPORT dynamic_array_t* make_dynamic_arr(size_t length) {
	dynamic_array_t* array = malloc(sizeof(dynamic_array_t));

	if (array == NULL) {
		return NULL;
	}

	array->length = length;
	array->start = malloc(ELEMENT_SIZE * length);

	if (array->start == NULL) {
		free(array);
		return NULL;
	}

	return array;
}

/**
 * void format_index(int* index, size_t length);
 * 
 * Formats a given `index` by wrapping it around a `length`.
 */
LIB_EXPORT void format_index(int* index, size_t length) {
	*index %= length;

	if (*index < 0) {
		*index += length;
	}
}

/**
 * void* dynamic_arr_at(dynamic_array_t* array, size_t index);
 *
 * Returns a pointer to the value at the specified index (type cast to get correct data).
 */
LIB_EXPORT size_t dynamic_arr_at(dynamic_array_t* array, int index) {
	if (array == NULL) {
		return 0;
	}

	format_index(&index, array->length);

	return array->start[index];
}

/**
 * void dynamic_arr_set(dynamic_array_t* array, size_t index, size_t value);
 *
 * Sets the value at `index` to `value` which can be cast to read.
 */
LIB_EXPORT void dynamic_arr_set(dynamic_array_t* array, int index, size_t value) {
	if (array == NULL) {
		return;
	}

	format_index(&index, array->length);

	*((size_t*)array->start + index) = value;
}

/**
 * void dynamic_arr_resize(dynamic_array_t* array, size_t length);
 *
 * Resizes a dynamic `array` based on the `length` of the `array`.
 */
LIB_EXPORT void dynamic_arr_resize(dynamic_array_t* array, size_t length) {
	if (array == NULL) {
		return;
	}

	void* new_start = realloc(array->start, ELEMENT_SIZE * length);

	if (new_start == NULL) {
		return;
	}

	array->start =  new_start;
	array->length = length;
}

/**
 * void dynamic_arr_append(dynamic_array_t* array, size_t value);
 *
 * Appends an element to a dynamic `array` by resizing it to be an element longer
 * and setting the last element to the input `value`.
 */
LIB_EXPORT void dynamic_arr_append(dynamic_array_t* array, size_t value) {
	if (array == NULL) {
		return;
	}

	dynamic_arr_resize(array, array->length + 1);
	dynamic_arr_set(array, array->length - 1, value);
}

/**
 * void dynamic_arr_pop(dynamic_array_t* array);
 *
 * Removes the last element of a dynamic `array` by resizing it to be one shorter.
 */
LIB_EXPORT void dynamic_arr_pop(dynamic_array_t* array) {
	if (array == NULL || array->length == 0) {
		return;
	}

	dynamic_arr_resize(array, array->length - 1);
}

/**
 * void dynamic_arr_destroy(dynamic_array_t* array);
 *
 * Properly cleans up the memory used by a dynamic_array_t.
 *
 * > Note: This will not clean up any memory used by elements within the array.
 */
LIB_EXPORT void dynamic_arr_destroy(dynamic_array_t* array) {
	if (array == NULL) {
		return;
	}

	free(array->start);
	array->start = NULL;

	free(array);
	array = NULL;
}

// EXTRA

/**
 * void dynamic_arr_print(dynamic_array_t* array, const char* name, char typeflag);
 * 
 * Prints a dynamic array assuming the data stored is of type `typeflag`.
 */
LIB_EXPORT void dynamic_arr_print(dynamic_array_t* array, const char* name, char typeflag) {
	if (array == NULL) {
		return;
	}

	printf("%s[%lu] { ", name, array->length);
	switch (typeflag) {
		case 'b':
			for (int i = 0; i < array->length - 1; i++) {
				printf("%i, ", ((int)dynamic_arr_at(array, i) != 0));
			}
			printf("%i", ((int)dynamic_arr_at(array, array->length - 1) != 0));
			break;
		case 'i':
			for (int i = 0; i < array->length - 1; i++) {
				printf("%i, ", (int)dynamic_arr_at(array, i));
			}
			printf("%i", (int)dynamic_arr_at(array, array->length - 1));
			break;
		case 'c':
			for (int i = 0; i < array->length - 1; i++) {
				printf("'%c', ", (char)dynamic_arr_at(array, i));
			}
			printf("'%c'", (char)dynamic_arr_at(array, array->length - 1));
			break;
		default:
			printf("Unknown/unsupported type");
			break;
	}
	printf(" }\n");
}

