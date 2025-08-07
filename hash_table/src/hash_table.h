#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include <stdbool.h>

#include "../../associative_array/src/associative_array.h"

typedef assoc_arr_t bucket_t;

typedef struct hmap {
	bucket_t* buckets;
	size_t size;
	size_t size_increase;
	bool multiply_size;
} hmap_t;

hmap_t* hmap_make(size_t start_size, size_t size_increase, bool multiply_size);
bool    hmap_add_pair(hmap_t* hmap, char* key, void* value);
bool    hmap_has_pair(hmap_t* hmap, char* key);
void*   hmap_get_pair(hmap_t* hmap, char* key);
bool    hmap_set_pair(hmap_t* hmap, char* key, void* value);
bool    hmap_remove_pair(hmap_t* hmap, char* key);
void    hmap_free(hmap_t* hmap);

#endif
