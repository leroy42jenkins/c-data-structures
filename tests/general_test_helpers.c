#include "general_test_helpers.h"


void console_set_black() { printf("\033[0;30m"); }

void console_set_red() { printf("\033[0;31m"); }

void console_set_green() { printf("\033[0;32m"); }

void console_set_yellow() { printf("\033[0;33m"); }

void console_set_blue() { printf("\033[0;34m"); }

void console_set_purple() { printf("\033[0;35m"); }

void console_set_cyan() { printf("\033[0;36m"); }

void console_set_white() { printf("\033[0;37m"); }

void run_tests_display_results(
	int argc,
	char **argv,
	void (**tests)(test_result *),
	size_t n_tests) {

	console_set_white();

	if (argc < 2 || strlen(argv[1]) < 1) {
		printf("tests range from %d to %li\n", 0, n_tests - 1);
		printf("usage example for test 0:\n");
		printf("./a.out 0\n");
		printf("usage example for all tests:\n");
		printf("./a.out a\n");
		return;
	}

	test_result t_r;

	t_r.successes = 0;
	t_r.failures = 0;

	if (argv[1][0] == 'a' || argv[1][0] == 'A') {
		for (size_t i = 0; i < n_tests; ++i) {
			tests[i](&t_r);
			printf("\n");
		}
	} else {
		int index = atoi(argv[1]);

		if (index < 0 || ((size_t)index) >= n_tests) {
			printf("test not found\n");
		} else {
			tests[index](&t_r);
			printf("\n");
		}
	}

	console_set_blue();
	printf("\n*** Test Summary ***\n\n");
	printf("{ successes: %i, failures: %i }\n\n", t_r.successes, t_r.failures);
	console_set_white();
}

