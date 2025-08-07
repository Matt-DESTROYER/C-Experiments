#ifndef HASH_FUNCTIONS_H
#define HASH_FUNCTIONS_H

#include <stdint.h>

/* STRING HASH FUNCTIONS */
unsigned long djb2(char* string);
unsigned long sdbm(char* string);
unsigned long fnv1a(char* string);

#endif

