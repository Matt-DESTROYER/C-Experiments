#ifndef DYNAMIC_ARRAY_H

#define NULL ((void*)0)

#define true  1
#define false 0

typedef unsigned int uint_t;

#define ELEMENT_SIZE sizeof(size_t)

typedef struct dynamic_array_t {
	size_t length;
	size_t* start;
} dynamic_array_t;

dynamic_array_t* make_dynamic_arr(size_t length);
size_t dynamic_arr_at(dynamic_array_t* array, int index);
void dynamic_arr_set(dynamic_array_t* array, size_t index, size_t value);
void dynamic_arr_resize(dynamic_array_t* array, size_t length);
void dynamic_arr_append(dynamic_array_t* array, size_t value);
void dynamic_arr_pop(dynamic_array_t* array);
void dynamic_arr_destroy(dynamic_array_t* array);

void dynamic_arr_print(dynamic_array_t* array, const char* name, char typeflag);

#endif
