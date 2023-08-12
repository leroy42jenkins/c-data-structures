#include "s_list.h"
#include "test_0.h"
#include "general_test_helpers.h"


/**
 * test functions
 */

void s_list_print_test_0(s_list *node) {
	if (node == NULL) {
		printf("list is NULL\n");	
		return;
	}

	printf("list elements: ");
	s_list_apply(node, test_0_print);
	printf("\n");
}

void test_0_push_pop_0(test_result *t_r) {
	test_0 *f = test_0_create(0, 'a');
	if (f == NULL) return;

	s_list *list = s_list_create((void *)f);
	if (list == NULL) {
		free(f);
		return;
	}

	printf("\nlist push and pop test 0\n");
	printf("list created\n");
	s_list_print_test_0(list);

	char c = 'a';
	for (int i = 1; i <= 3; ++i) {
		test_0 *t = test_0_create(i, c);
		if (t == NULL) continue;

		int r = s_list_push(&list, (void *)t);
		if (r == 0) {
			t_r->successes += 1;
			console_set_green();
			printf("success: element %i pushed\n", i);
			console_set_white();
		} else {
			t_r->failures += 1;
			console_set_red();
			printf("failure: element %i not pushed\n", i);
			console_set_white();
			free(t);
		}
	}

	s_list_print_test_0(list);

	for (int i = 3; i >= 0; --i) {
		void *v = s_list_pop(&list);

		if (v == NULL) {	
			t_r->failures += 1;
			console_set_red();
			printf("failure: element %i not found\n", i);
			console_set_white();
			continue;
		}

		test_0 *t = (test_0 *)v;
		
		if (t->n == i) {
			t_r->successes += 1;
			console_set_green();
			printf("success: element %i found in correct order\n", i);
			console_set_white();
		} else {
			t_r->failures += 1;
			console_set_red();
			printf("failure: element %i not found in correct order\n", i);
			console_set_white();
		}

		test_0_destroy((void *)t);
	}

	s_list_print_test_0(list);
	s_list_destroy(&list);	
	
	if (list != NULL) {
                t_r->failures += 1;
                console_set_red();
                printf("failure: list is not NULL after destruction");
                console_set_white();
        } else {
                printf("list destroyed");
        }
	
	printf("\n\n");
}


/**
 * main
 */

int main(int argc, char **argv) {
	void (*tests[1])(test_result *) = {
		test_0_push_pop_0
	};

	run_tests_display_results(argc, argv, tests, 1);
	return 0;
}

