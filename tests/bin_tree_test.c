#include "bin_tree.h"
#include "test_0.h"
#include "general_test_helpers.h"


/**
 * test variables
*/

#define BUFFER_SIZE 10

test_0 test_0_in[BUFFER_SIZE];
test_0 test_0_out[BUFFER_SIZE];

int test_0_out_i = 0;


/**
 * test helper functions
 */

void configure_buffer_defaults() {
	for (int i = 0; i < BUFFER_SIZE; ++i) {
		test_0_configure(test_0_in + i, i, 'z');
		test_0_configure(test_0_out + i, i, 'z');
	}
}

void populate_out_buffer_from_tree(bin_tree *node, int size) {
	if (node == NULL ||
		node->element == NULL ||
		test_0_out_i >= size ||
		test_0_out_i >= BUFFER_SIZE) return;

	populate_out_buffer_from_tree(node->left, size);
	test_0 *t_0 = (test_0 *)node->element;
	test_0 *u_0 = test_0_out + test_0_out_i;
	test_0_copy(t_0, u_0);
	test_0_out_i += 1;
	populate_out_buffer_from_tree(node->right, size);
}

int compare_buffers(int size) {
	for (int i = 0; i < size && i < BUFFER_SIZE; ++i) {
		int r = strcmp(test_0_in[i].s, test_0_out[i].s);
		if (r != 0) return r;
	}

	return 0;
}

void print_buffer(test_0 *buffer, int size) {
	for (int i = 0; i < size && i < BUFFER_SIZE; ++i) {
		test_0 t_0 = buffer[i];
		printf("{%i, %s} ", t_0.n, t_0.s);
	}

	printf("\n");
}


/**
 * test functions
 */

void test_0_insert_0(test_result *t_r) {
	test_0_out_i = 0;

	printf("\n\n");
}


/**
 * main
 */

int main(int argc, char **argv) {
	configure_buffer_defaults();

	void (*tests[1])(test_result *) = {
		test_0_insert_0
	};

	run_tests_display_results(argc, argv, tests, 1);
	return 0;
}

