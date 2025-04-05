#include <stdlib.h>

#include "dynamic_array.h"

/**
 * dynamic_array_t* make_dynamic_arr(uint_t length, uint_t size);
 *
 * Properly initializes a dynamic_array_t structure with a given `length` of elements
 * and a give `size` of each individual element (eg `sizeof(int)`).
 */
dynamic_array_t* make_dynamic_arr(uint_t length) {
	dynamic_array_t* arr = malloc(sizeof(dynamic_array_t));

	arr->length = length;
	arr->start = malloc(ELEMENT_SIZE * length);

	return arr;
}

/**
 * void* dynamic_arr_at(dynamic_array_t* array, uint_t index);
 *
 * Returns a pointer to the value at the specified index (type cast to get correct data).
 */
uint_t dynamic_arr_at(dynamic_array_t* array, int index) {
	index %= array->length;

	if (index < 0) {
		index += array->length;
	}

	return array->start[index];
}

/**
 * void dynamic_arr_set(dynamic_array_t* array, uint_t index, uint_t value);
 *
 * Sets the value at `index` to `value` which can be cast to read.
 */
void dynamic_arr_set(dynamic_array_t* array, uint_t index, uint_t value) {
	*((uint_t*)array->start + index) = value;
}

/**
 * void dynamic_arr_resize(dynamic_array_t* array, uint_t length);
 *
 * Resizes a dynamic `array` based on the `length` of the `array`.
 */
void dynamic_arr_resize(dynamic_array_t* array, uint_t length) {
	void* new_array = malloc(ELEMENT_SIZE * length);

	uint_t elements_to_copy = (array->length < length) ? array->length : length;

	for (uint_t i = 0; i < elements_to_copy; i++) {
		*((uint_t*)new_array + i) = *((uint_t*)array->start + i);
	}

	free(array->start);
	array->start = new_array;

	array->length = length;
}

/**
 * void dynamic_arr_append(dynamic_array_t* array, uint_t value);
 *
 * Appends an element to a dynamic `array` by resizing it to be an element longer
 * and setting the last element to the input `value`.
 */
void dynamic_arr_append(dynamic_array_t* array, uint_t value) {
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
