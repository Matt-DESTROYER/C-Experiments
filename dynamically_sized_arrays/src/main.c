#include <stdio.h>

#include "dynamic_array.h"

int main(int argc, char* argv[]) {
	/* --------------------------------------------------------------- */

	printf("Demo #1\n-------\nArray of multiples of 5 of length n (input a positive integer): ");

	size_t array1_length;
	scanf("%lu", &array1_length);

	// create a dynamic array
	dynamic_array_t* array1 = make_dynamic_arr(array1_length /* array length */);

	// set every i'th element to (i*5)
	for (int i = 0; i < array1->length; i++) {
		dynamic_arr_set(/* array (pointer) */ array1, /* index */ i, /* value */ i*5);
	}

	// print the array
	dynamic_arr_print(array1 /* array (pointer) */, "array1" /* array name (const char*) */, 'i' /* typeflag (b = bool, i = int, c = char) */);
	printf("\n\n");

	/* --------------------------------------------------------------- */

	printf("Demo #2\n-------\nArray of chars of length n (input a positive integer): ");

	size_t array2_length;
	scanf("%lu", &array2_length);

	// create another dynamic array
	dynamic_array_t* array2 = make_dynamic_arr(array2_length);

	// set every i'th element to (char)
	for (int i = 0; i < array2->length; i++) {
		dynamic_arr_set(array2, i, (char)(i+32));
	}

	// print the array
	dynamic_arr_print(array2, "array2", 'c');
	printf("\n\n");

	/* --------------------------------------------------------------- */
	
	printf("Demo #3\n-------\nExtend the array by n (input a positive integer): ");

	size_t array2_extension;
	scanf("%lu", &array2_extension);

	// resize the array

	dynamic_arr_resize(array2 /* array (pointer) */, array2_length + array2_extension /* new array size */);

	// extend the array
	for (int i = array2_length; i < array2->length; i++) {
		dynamic_arr_set(array2, i, (char)(i+32));
	}

	// print the array
	dynamic_arr_print(array2, "array2", 'c');
	printf("\n\n");

	/* --------------------------------------------------------------- */

	printf("Demo #4\n-------\nAppend n (input a positive integer) multiples of 5 to the end of the first array (array1): ");

	size_t array1_extension;
	scanf("%lu", &array1_extension);

	// append n multiples of 5 (array1->length + i) * 5
	for (int i = 0; i < array1_extension; i++) {
		dynamic_arr_append(array1 /* array (pointer) */, (array1->length + i) * 5 /* value */);
	}

	// print the array
	dynamic_arr_print(array1, "array1", 'i');
	printf("\n\n");

	/* --------------------------------------------------------------- */

	// clean up the memory used
	dynamic_arr_destroy(array1 /* array (pointer) */);
	dynamic_arr_destroy(array2);	

	/* --------------------------------------------------------------- */

	return 0;
}
