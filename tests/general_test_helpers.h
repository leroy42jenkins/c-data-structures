#ifndef GENERAL_TEST_HELPERS
#define GENERAL_TEST_HELPERS


#include <stdlib.h>
#include <stdio.h>
#include <string.h>


typedef struct test_result_t {
	int successes;
	int failures;
} test_result;


void console_set_black(void);

void console_set_red(void);

void console_set_green(void);

void console_set_yellow(void);

void console_set_blue(void);

void console_set_purple(void);

void console_set_cyan(void);

void console_set_white(void);

void run_tests_display_results(int, char **, void (**)(test_result *), size_t);


#endif

