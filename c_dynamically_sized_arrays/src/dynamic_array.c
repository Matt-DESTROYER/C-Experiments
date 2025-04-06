#include <stdlib.h>
#include <stdio.h>

#include "dynamic_array.h"

/**
 * dynamic_array_t* make_dynamic_arr(size_t length, size_t size);
 *
 * Properly initializes a dynamic_array_t structure with a given `length` of elements
 * and a give `size` of each individual element (eg `sizeof(int)`).
 */
dynamic_array_t* make_dynamic_arr(size_t length) {
	dynamic_array_t* arr = malloc(sizeof(dynamic_array_t));

	arr->length = length;
	arr->start = malloc(ELEMENT_SIZE * length);

	return arr;
}

/**
 * void* dynamic_arr_at(dynamic_array_t* array, size_t index);
 *
 * Returns a pointer to the value at the specified index (type cast to get correct data).
 */
size_t dynamic_arr_at(dynamic_array_t* array, int index) {
	index %= array->length;

	if (index < 0) {
		index += array->length;
	}

	return array->start[index];
}

/**
 * void dynamic_arr_set(dynamic_array_t* array, size_t index, size_t value);
 *
 * Sets the value at `index` to `value` which can be cast to read.
 */
void dynamic_arr_set(dynamic_array_t* array, size_t index, size_t value) {
	*((size_t*)array->start + index) = value;
}

/**
 * void dynamic_arr_resize(dynamic_array_t* array, size_t length);
 *
 * Resizes a dynamic `array` based on the `length` of the `array`.
 */
void dynamic_arr_resize(dynamic_array_t* array, size_t length) {
	void* new_array = malloc(ELEMENT_SIZE * length);

	size_t elements_to_copy = (array->length < length) ? array->length : length;

	for (size_t i = 0; i < elements_to_copy; i++) {
		*((size_t*)new_array + i) = *((size_t*)array->start + i);
	}

	free(array->start);
	array->start = new_array;

	array->length = length;
}

/**
 * void dynamic_arr_append(dynamic_array_t* array, size_t value);
 *
 * Appends an element to a dynamic `array` by resizing it to be an element longer
 * and setting the last element to the input `value`.
 */
void dynamic_arr_append(dynamic_array_t* array, size_t value) {
	dynamic_arr_resize(array, array->length + 1);
	dynamic_arr_set(array, array->length - 1, value);
}

/**
 * void dynamic_arr_pop(dynamic_array_t* array);
 *
 * Removes the last element of a dynamic `array` by resizing it to be one shorter.
 */
void dynamic_arr_pop(dynamic_array_t* array) {
	dynamic_arr_resize(array, array->length - 1);
}

/**
 * void dynamic_arr_destroy(dynamic_array_t* array);
 *
 * Properly cleans up the memory used by a dynamic_array_t.
 *
 * > Note: This will not clean up any memory used by elements within the array.
 */
void dynamic_arr_destroy(dynamic_array_t* array) {
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
void dynamic_arr_print(dynamic_array_t* array, const char* name, char typeflag) {
	printf("%s[%lu] { ", name, array->length);
	switch (typeflag) {
		case 'b':
			for (int i = 0; i < array->length; i++) {
				printf("%i, ", ((int)dynamic_arr_at(array, i) != 0));
			}
			break;
		case 'i':
			for (int i = 0; i < array->length; i++) {
				printf("%i, ", (int)dynamic_arr_at(array, i));
			}
			break;
		case 'c':
			for (int i = 0; i < array->length; i++) {
				printf("'%c', ", (char)dynamic_arr_at(array, i));
			}
			break;
		default:
			printf("Unknown/unsupported type");
			break;
	}
	printf("}\n");
}
