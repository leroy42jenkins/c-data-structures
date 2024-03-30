#ifndef TEST_0_H
#define TEST_0_H


#include <stdlib.h>
#include <stdio.h>
#include <string.h>


/**
 * test element 0
 */

typedef struct test_0_t {
	int n;
	char s[5];
} test_0;

void test_0_configure(test_0 *, int, char);

void test_0_copy(test_0 *, test_0 *);

test_0 * test_0_create(int, char);

int test_0_compare(void *, void *);

void test_0_destroy(void *);

void test_0_print(void *);


#endif

