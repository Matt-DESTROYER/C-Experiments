#include <stdlib.h>
#include <stdio.h>

#include "binary_tree.h"

int main(int argc, char* argv[]) {
	binary_tree_t* tree = make_binary_tree();

	destroy_binary_tree(tree);

	return 0;
}

