#ifndef DYNAMIC_ARRAY_H

#define NULL ((void*)0)

typedef unsigned int uint_t;

#define ELEMENT_SIZE sizeof(uint_t)

typedef struct dynamic_array_t {
	uint_t length;
	uint_t* start;
} dynamic_array_t;

dynamic_array_t* make_dynamic_arr(uint_t length);
uint_t dynamic_arr_at(dynamic_array_t* array, int index);
void dynamic_arr_set(dynamic_array_t* array, uint_t index, uint_t value);
void dynamic_arr_resize(dynamic_array_t* array, uint_t length);
void dynamic_arr_append(dynamic_array_t* array, uint_t value);
void dynamic_arr_pop(dynamic_array_t* array);
void dynamic_arr_destroy(dynamic_array_t* array);

#endif
