#ifndef ASSOCIATIVE_ARRAY_H
#define ASSOCIATIVE_ARRAY_H

#include <stdlib.h>
#include <stdbool.h>

#define NULL_CHAR '\0'

#define SUCCESS true
#define FAILURE false

typedef struct assoc_pair assoc_pair_t;
struct assoc_pair {
	char* key;
	void* value;

	assoc_pair_t* next;
};

typedef struct assoc_arr {
	size_t size;

	assoc_pair_t* head;
	assoc_pair_t* tail;
} assoc_arr_t;

assoc_arr_t* assoc_make(void);
bool         assoc_add(assoc_arr_t* arr, char* key, void* value);
bool         assoc_has(assoc_arr_t* arr, char* key);
void*        assoc_get(assoc_arr_t* arr, char* key);
bool         assoc_set(assoc_arr_t* arr, char* key, void* value);
bool         assoc_remove(assoc_arr_t* arr, char* key);
void         assoc_free(assoc_arr_t* arr);

#endif
