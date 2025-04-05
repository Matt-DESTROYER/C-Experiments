#include <stdio.h>

#include "dynamic_array.h"

void dynamic_arr_print_int(dynamic_array_t* array, const char* name);
void dynamic_arr_print_char(dynamic_array_t* array, const char* name);

int main(int argc, char* argv[]) {
	/* --------------------------------------------------------------- */

	printf("Demo #1\n-------\nArray of multiples of 5 of length n (input a positive integer): ");

	uint_t array1_length;
	scanf("%u", &array1_length);

	// create a dynamic array
	dynamic_array_t* array1 = make_dynamic_arr(array1_length);

	// set every i'th element to (i*5)
	for (int i = 0; i < array1->length; i++) {
		dynamic_arr_set(/* array (pointer) */ array1, /* index */ i, /* value */ i*5);
	}

	// print the array
	dynamic_arr_print_int(array1, "array1");
	printf("\n\n");

	/* --------------------------------------------------------------- */

	printf("Demo #2\n-------\nArray of chars of length n (input a positive integer): ");

	uint_t array2_length;
	scanf("%u", &array2_length);

	// create another dynamic array
	dynamic_array_t* array2 = make_dynamic_arr(array2_length);

	// set every i'th element to (char)
	for (int i = 0; i < array2->length; i++) {
		dynamic_arr_set(array2, i, (char)(i+32));
	}

	// print the array
	dynamic_arr_print_char(array2, "array2");
	printf("\n\n");

	/* --------------------------------------------------------------- */
	
	printf("Demo #3\n-------\nExtend the array by n (input a positive integer): ");

	uint_t array2_extension;
	scanf("%u", &array2_extension);

	// resize the array

	dynamic_arr_resize(array2, array2_length + array2_extension);

	// extend the array
	for (int i = array2_length; i < array2->length; i++) {
		dynamic_arr_set(array2, i, (char)(i+32));
	}

	// print the array
	dynamic_arr_print_char(array2, "array2");
	printf("\n\n");

	/* --------------------------------------------------------------- */

	printf("Demo #4\n-------\nAppend n (input a positive integer) multiples of 5 to the end of the first array (array1): ");

	uint_t array1_extension;
	scanf("%u", &array1_extension);

	// append n multiples of 5 (array1->length + i) * 5
	for (int i = 0; i < array1_extension; i++) {
		dynamic_arr_append(array1, (array1->length + i) * 5);
	}

	// print the array
	dynamic_arr_print_int(array1, "array1");
	printf("\n\n");

	/* --------------------------------------------------------------- */

	// clean up the memory used
	dynamic_arr_destroy(array1);
	dynamic_arr_destroy(array2);	

	/* --------------------------------------------------------------- */

	return 0;
}

void dynamic_arr_print_int(dynamic_array_t* array, const char* name) {
	printf("%s[%u] { ", name, array->length);
	for (int i = 0; i < array->length; i++) {
		printf("%i, ", (int)dynamic_arr_at(array, i));
	}
	printf("}\n");
}
void dynamic_arr_print_char(dynamic_array_t* array, const char* name) {
	printf("%s[%u] { ", name, array->length);
	for (int i = 0; i < array->length; i++) {
		printf("%c, ", (char)dynamic_arr_at(array, i));
	}
	printf("}\n");
}
