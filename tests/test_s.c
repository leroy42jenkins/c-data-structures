#include "test_s.h"


char get_rand_char_a_z() {
	int r = rand();
	if (r < 0) r *= -1;
	return 'a' + (char)(r % 26);
}

int test_s_configure_length(test_s *t, size_t length) {
	if (t == NULL) return -1;

	if (length > 9) length = 9;
	
	for (size_t i = 0; i < length; ++i)
                t->s[i] = get_rand_char_a_z();

	t->s[length] = '\0';
	return 0;
}

int test_s_compare(void *v, void *w) {
	test_s *t = (test_s *)v;
	test_s *u = (test_s *)w;

	return (t == NULL || u == NULL)
		? 0
		: strcmp(t->s, u->s);
}

void test_s_print(void *v) {
	test_s *t = (test_s *)v;
	if (t == NULL) return;
	printf("{%s} ", t->s);
}

