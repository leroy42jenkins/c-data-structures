#include "bin_tree.h"
#include "test_0.h"
#include "general_test_helpers.h"


/**
 * test variables
*/

#define BUFFER_SIZE 10

test_0 test_0_in[BUFFER_SIZE];
test_0 test_0_expected[BUFFER_SIZE];
test_0 test_0_out[BUFFER_SIZE];

int test_0_out_i = 0;


/**
 * test helper functions
 */

void configure_buffer_defaults() {
	for (int i = 0; i < BUFFER_SIZE; ++i) {
		test_0_configure(test_0_in + i, i, 'z');
		test_0_configure(test_0_expected + i, i, 'z');
		test_0_configure(test_0_out + i, i, 'z');
	}

	test_0_out_i = 0;
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

int compare_out_buffer_to_expected(int size) {
	for (int i = 0; i < size && i < BUFFER_SIZE; ++i) {
		int r = strcmp(test_0_expected[i].s, test_0_out[i].s);
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
    printf("\nbinary search tree insertion test 0\n");
	
	configure_buffer_defaults();
	bin_tree *root = NULL;
	int size = 6;

	test_0_configure(test_0_in, 0, 'd');
	test_0_configure(test_0_in + 1, 1, 'f');
	test_0_configure(test_0_in + 2, 2, 'e');
	test_0_configure(test_0_in + 3, 3, 'b');
	test_0_configure(test_0_in + 4, 4, 'a');
	test_0_configure(test_0_in + 5, 5, 'c');

	for (int i = 0; i < size; ++i) {
		void *v = (void *)(test_0_in + i);
		root = bin_tree_insert(root, v, test_0_compare);
	}

	test_0_configure(test_0_expected, 0, 'a');
	test_0_configure(test_0_expected + 1, 1, 'b');
	test_0_configure(test_0_expected + 2, 2, 'c');
	test_0_configure(test_0_expected + 3, 3, 'd');
	test_0_configure(test_0_expected + 4, 4, 'e');
	test_0_configure(test_0_expected + 5, 5, 'f');

	populate_out_buffer_from_tree(root, size);

	printf("in:\t\t");
	print_buffer(test_0_in, size);
	printf("expected:\t");
	print_buffer(test_0_expected, size);
	printf("out:\t\t");
	print_buffer(test_0_out, size);

	int r = compare_out_buffer_to_expected(size);

	if (r == 0) {
		t_r->successes += 1;
		console_set_green();
		printf("success: elements match what is expected\n");
		console_set_white();
	} else {
		t_r->failures += 1;
		console_set_red();
		printf("failure: elements do not match what is expected\n");
		console_set_white();
	}

	root = bin_tree_destroy(root);

	printf("\n\n");
}


/**
 * main
 */

int main(int argc, char **argv) {
	void (*tests[1])(test_result *) = {
		test_0_insert_0
	};

	run_tests_display_results(argc, argv, tests, 1);
	return 0;
}

