#include "binary_tree.h"

binary_tree_t* make_binary_tree() {
	binary_tree_t* tree = (binary_tree_t*)malloc(sizeof(binary_tree_t));

	tree->length = 0;
	tree->left = NULL;
	tree->right = NULL;

	return tree;
}

