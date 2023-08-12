#include "test_0.h"


void test_0_configure(test_0 *t, int n, char c) {
	t->n = n;
	t->s[0] = c;
	t->s[1] = (c + 1) % 127;
	t->s[2] = (c + 2) % 127;
	t->s[3] = (c + 3) % 127;
	t->s[4] = '\0';
}

test_0 * test_0_create(int n, char c) {
	test_0 *t = malloc(sizeof (test_0));	
	if (t == NULL) return NULL;
	test_0_configure(t, n, c);
	return t;
}

int test_0_compare(void *v, void *w) {
	if (v == NULL || w == NULL) return 0;
	test_0 *t = (test_0 *)v;
	test_0 *u = (test_0 *)w;
	return strcmp(t->s, u->s);
}

void test_0_destroy(void *v) {
	if (v == NULL) return;
	test_0 *t = (test_0 *)v;
	free(t);
}

void test_0_print(void *v) {
	if (v == NULL) return;	
	test_0 *t = (test_0 *)v;
	printf("{%i, %s} ", t->n, t->s);
}

