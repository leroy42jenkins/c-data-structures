#include "d_list.h"
#include "test_0.h"
#include "general_test_helpers.h"


/**
 * test functions
 */

void d_list_print_test_0(d_list *list) {
	if (list == NULL) {
		printf("list is NULL\n");	
		return;
	}

	if (list->size == 0) {
		printf("list is empty\n");
		return;
	}

	printf("list elements: ");
	d_list_node *t = list->front;

	while (t != NULL) {
		test_0_print(t->element);
		t = t->back;
	}
	
	printf("\n");
}

void test_0_configure_array(test_0 *test_array, size_t size) {
        char c = 'a';
        for (size_t i = 0; i < size; ++i) {
                test_0_configure(&(test_array[i]), (int)i, c);
                c = c >= 'x' ? 'a' : c + 1;
        }
}

void test_0_push_pop_front_0(test_result *t_r) {
	size_t size = 6;
        test_0 test_array[size];
        test_0_configure_array(test_array, size);

        printf("\ndoubly linked list push front and pop front test 0\n");

        d_list *list = d_list_create();
        if (list == NULL) return;

        printf("list created\n");
        d_list_print_test_0(list);

        for (size_t i = 0; i < size; ++i) {
                test_0 *t = &(test_array[i]);
                int r = d_list_push_front(list, (void *)t);

                if (r == 0) {
                        t_r->successes += 1;
                        console_set_green();
                        printf("success: element %i pushed\n", (int)i);
                        console_set_white();
                } else {
                        t_r->failures += 1;
                        console_set_red();
                        printf("failure: element %i not pushed\n", (int)i);
                        console_set_white();
                }
        }

	d_list_print_test_0(list);

	for (int i = (int)(size - 1); i >= 0; --i) {
                void *v = d_list_pop_front(list);

                if (v == NULL) {
                        t_r->failures += 1;
                        console_set_red();
                        printf("failure: element %i element not found\n", i);
                        console_set_white();
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
        }

        d_list_print_test_0(list);
        d_list_destroy(&list);

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

void test_0_push_pop_back_1(test_result *t_r) {
	size_t size = 6;
        test_0 test_array[size];
        test_0_configure_array(test_array, size);

        printf("\ndoubly linked list push back and pop back test 1\n");

        d_list *list = d_list_create();
        if (list == NULL) return;

        printf("list created\n");
        d_list_print_test_0(list);

        for (size_t i = 0; i < size; ++i) {
                test_0 *t = &(test_array[i]);
                int r = d_list_push_back(list, (void *)t);

                if (r == 0) {
                        t_r->successes += 1;
                        console_set_green();
                        printf("success: element %i pushed\n", (int)i);
                        console_set_white();
                } else {
                        t_r->failures += 1;
                        console_set_red();
                        printf("failure: element %i not pushed\n", (int)i);
                        console_set_white();
                }
        }

	d_list_print_test_0(list);

	for (int i = (int)(size - 1); i >= 0; --i) {
                void *v = d_list_pop_back(list);

                if (v == NULL) {
                        t_r->failures += 1;
                        console_set_red();
                        printf("failure: element %i element not found\n", i);
                        console_set_white();
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
        }

        d_list_print_test_0(list);
        d_list_destroy(&list);

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
	void (*tests[2])(test_result *) = {
		test_0_push_pop_front_0,
		test_0_push_pop_back_1
	};

	run_tests_display_results(argc, argv, tests, 2);

	return 0;
}

