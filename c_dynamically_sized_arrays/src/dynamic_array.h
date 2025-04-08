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

#ifdef BUILDING_SHARED
	#if defined _WIN32 || defined __CYGWIN__
		#define LIB_EXPORT __declspec(dllexport)
	#elif __GNUC__ >= 4
		#define LIB_EXPORT __attribute__((visibility ("default")))
	#endif
#endif
#ifndef LIB_EXPORT
	#define LIB_EXPORT
#endif

LIB_EXPORT dynamic_array_t* make_dynamic_arr(size_t length);
LIB_EXPORT size_t dynamic_arr_at(dynamic_array_t* array, int index);
LIB_EXPORT void dynamic_arr_set(dynamic_array_t* array, int index, size_t value);
LIB_EXPORT void dynamic_arr_resize(dynamic_array_t* array, size_t length);
LIB_EXPORT void dynamic_arr_append(dynamic_array_t* array, size_t value);
LIB_EXPORT void dynamic_arr_pop(dynamic_array_t* array);
LIB_EXPORT void dynamic_arr_destroy(dynamic_array_t* array);

LIB_EXPORT void dynamic_arr_print(dynamic_array_t* array, const char* name, char typeflag);

#endif
