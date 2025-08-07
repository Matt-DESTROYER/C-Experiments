#include "associative_array.h"

static size_t string_length(char* str) {
	size_t length = 0;
	while (str[length] != NULL_CHAR) {
		length++;
	}
	return length;
}

static char* copy_string(char* str) {
	char* res = malloc(string_length(str) * sizeof(char) + 1);
	if (res == NULL) {
		return NULL;
	}
	size_t index = 0;
	while (str[index] != NULL_CHAR) {
		res[index] = str[index];
		index++;
	}
	res[index] = NULL_CHAR;
	return res;
}

assoc_arr_t* assoc_make() {
	assoc_arr_t* arr = malloc(sizeof(assoc_arr_t));
	if (arr == NULL) {
		return NULL;
	}

	arr->size = 0;
	arr->head = NULL;
	arr->tail = NULL;

	return arr;
}

bool assoc_add(assoc_arr_t* arr, char* key, void* value) {
	assoc_pair_t* pair = malloc(sizeof(assoc_pair_t));
	if (pair == NULL) {
		return FAILURE;
	}

	pair->key = copy_string(key);
	pair->value = value;

	if (arr->tail == NULL) {
		arr->tail = pair;
		arr->head = pair;
	} else {
		arr->tail->next = pair;
		arr->tail = pair;
	}

	arr->size++;

	return SUCCESS;
}

static bool key_equals(char* key1, char* key2) {
	size_t index = 0;

	while (key1[index] != NULL_CHAR &&
			key2[index] != NULL_CHAR) {
		if (key1[index] != key2[index]) {
			return false;
		}

		index++;
	}

	if (key1[index] != NULL_CHAR ||
			key2[index] != NULL_CHAR) {
		return false;
	}

	return true;
}

bool assoc_has(assoc_arr_t* arr, char* key) {
	assoc_pair_t* node = arr->head;
	if (node == NULL) {
		return false;
	}

	for (size_t i = 0; i < arr->size; i++) {
		if (key_equals(key, node->key)) {
			return true;
		}
		node = node->next;

		// handle malformed dictionaries
		if (node->next == NULL) {
			arr->size = i + 1;
			return false;
		}
	}

	return false;
}

void* assoc_get(assoc_arr_t* arr, char* key) {
	assoc_pair_t* node = arr->head;

	for (size_t i = 0; i < arr->size; i++) {
		if (node == NULL) {
			arr->size = i; // in case of malformed associative arrays
			return NULL;
		}

		if (key_equals(key, node->key)) {
			return node->value;
		}

		node = node->next;
	}

	return NULL;
}

bool assoc_set(assoc_arr_t* arr, char* key, void* value) {
	assoc_pair_t* node = arr->head;

	for (size_t i = 0; i < arr->size; i++) {
		if (node == NULL) {
			arr->size = i;
			return FAILURE;
		}

		if (key_equals(key, node->key)) {
			// Should we free a pointer not malloc'ed by us?
			//free(node->value);
			node->value = value;
			return SUCCESS;
		}

		node = node-> next;
	}
	
	return FAILURE;
}

static void free_pair(assoc_pair_t* pair) {
	free(pair->key);
	// Should we free a pointer not malloc'ed by us?
	//free(pair->value);
	free(pair);
}

bool assoc_remove(assoc_arr_t* arr, char* key) {
	assoc_pair_t* curr_node = arr->head;
	if (curr_node == NULL) {
		return FAILURE;
	} else if (key_equals(curr_node->key, key)) {
		arr->head = curr_node->next;
		free_pair(curr_node);
		return SUCCESS;
	}

	assoc_pair_t* prev_node = curr_node;
	for (size_t i = 1; i < arr->size - 1; i++) {
		curr_node = curr_node->next;

		// handle malformed dictionaries
		if (curr_node == NULL) {
			arr->size = i;
			return FAILURE;
		} else if (key_equals(key, curr_node->key)) {
			prev_node->next = curr_node->next;
			free_pair(curr_node);
			return SUCCESS;
		}
		prev_node = curr_node;
	}
	return FAILURE;
}

void assoc_free(assoc_arr_t* arr) {
	assoc_pair_t* node = arr->head;
	while (node != NULL) {
		assoc_pair_t* next_node = node->next;
		free_pair(node);
		node = next_node;
	}
	free(arr);
}
