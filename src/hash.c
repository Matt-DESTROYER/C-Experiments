#include "hash.h"

unsigned long djb2(char* string) {
	unsigned long hash = 5281;
	int chr;
	while ((chr = *string++)) {
		hash = ((hash << 5) + hash) + chr; // hash * 33 + c
	}
	return hash;
}

unsigned long sdbm(char* string) {
	unsigned long hash = 0;
	int chr;
	while ((chr = *string++)) {
		hash = chr + (hash << 6) + (hash << 16) - hash;
	}
	return hash;
}

uint32_t fnv1a(char* string) {
	uint32_t hash = 2166136261u;
	while (*str) {
		hash = (hash ^ (unsigned char)(*str++) * 16777619u;
	}
	return hash;
}

