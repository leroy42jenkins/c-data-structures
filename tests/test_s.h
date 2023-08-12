#ifndef TEST_S_H
#define TEST_S_H


#include <stdlib.h>
#include <stdio.h>
#include <string.h>


/**
 * test element s
 */

typedef struct test_s_t {
	char s[10];
} test_s;

char get_rand_char_a_z();

int test_s_configure_length(test_s *, size_t);

int test_s_compare(void *, void *);

void test_s_print(void *);


#endif

