#include <stdlib.h>
#include <stdio.h>

#include "associative_array.h"

int main(int argc, char* argv[]) {
	assoc_arr_t* arr = assoc_make();

	int num = 123;

	add_pair(arr, "test", (void*)&num);

	printf("arr[\"num\"] = %d\n", *((int*)get_pair(arr, "test")));

	printf("Size: %lu\n", arr->size);

	return EXIT_SUCCESS;
}
