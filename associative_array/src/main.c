#include <stdlib.h>
#include <stdio.h>

#include "associative_array.h"

typedef associative_array_t ass_arr_t;

int main(int argc, char* argv[]) {
	ass_arr_t* arr = make_associative_array();

	int num = 123;

	add_pair(arr, "test", (void*)&num);

	printf("arr[\"num\"] = %d\n", *((int*)get_pair(arr, "test")));

	printf("Size: %lu\n", arr->size);

	return EXIT_SUCCESS;
}

