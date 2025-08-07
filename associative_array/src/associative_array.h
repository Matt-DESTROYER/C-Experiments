#ifndef ASSOCIATIVE_ARRAY_H
#define ASSOCIATIVE_ARRAY_H

#include <stdlib.h>
#include <stdbool.h>

#define NULL_CHAR '\0'

#define SUCCESS true
#define FAILURE false

typedef struct array_pair array_pair_t;
struct array_pair {
	char* key;
	void* value;

	array_pair_t* next;
};

typedef struct associative_array {
	size_t size;

	array_pair_t* head;
	array_pair_t* tail;
} associative_array_t;

associative_array_t* make_associative_array(void);
bool                 add_pair(associative_array_t* arr, char* key, void* value);
bool                 has_pair(associative_array_t* arr, char* key);
void*                get_pair(associative_array_t* arr, char* key);
bool                 set_pair(associative_array_t* arr, char* key, void* value);
bool                 remove_pair(associative_array_t* arr, char* key);

#endif

