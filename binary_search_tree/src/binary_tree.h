#include <stdlib.h>

typedef struct binary_tree_node {
	struct binary_tree_node* left;
	struct binary_tree_node* right;
} binary_tree_node_t;

typedef struct binary_tree {
	size_t length;
	binary_tree_node_t* root;
} binary_tree_t;

binary_tree_t* make_binary_tree();
void           destroy_binary_tree(binary_tree_t* tree);


