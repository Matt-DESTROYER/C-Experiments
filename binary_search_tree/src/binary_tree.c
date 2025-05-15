#include "binary_tree.h"

binary_tree_t* make_binary_tree() {
	binary_tree_t* tree = (binary_tree_t*)malloc(sizeof(binary_tree_t));

	tree->length = 0;
	tree->root = NULL;

	return tree;
}

void destroy_binary_tree_node(binary_tree_node_t* node) {
	if (node == NULL)
		return;

	destroy_binary_tree_node(node->left);
	destroy_binary_tree_node(node->right);

	free(node->left);
	free(node->right);
}

void destroy_binary_tree(binary_tree_t* tree) {
	if (tree == NULL)
		return;

	destroy_binary_tree_node(tree->root);
	free(tree);
}

