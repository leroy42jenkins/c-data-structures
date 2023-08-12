#include <time.h>


#include "h_table.h"
#include "hash_helpers.h"
#include "test_s.h"
#include "general_test_helpers.h"


/**
 * test helpers
 */

#define BOUNDARY_0 65521

size_t test_s_hash_xor8(void *v) {
	test_s *t = (test_s *)v;
	uint8_t h = hash_xor8(t->s);
	return (size_t)h;
}

size_t test_s_hash_adler32(void *v) {
	test_s *t = (test_s *)v;
	uint32_t h = hash_adler32(t->s);
	return (size_t)h;
}

size_t test_s_hash_crc32(void *v) {
	test_s *t = (test_s *)v;
	uint32_t h = hash_crc32(t->s);
	return (size_t)h;
}

size_t test_s_hash_djb2(void *v) {
	test_s *t = (test_s *)v;
	uint64_t h = hash_djb2(t->s);
	return (size_t)h;
}

size_t test_s_hash_sdbm(void *v) {
	test_s *t = (test_s *)v;
	uint64_t h = hash_sdbm(t->s);
	return (size_t)h;
}

void h_table_populate_rand(
	test_s *test_array,
	size_t test_array_size,
	h_table *table,
	size_t (*hash)(void *),
	test_result *t_r) {

	if (test_array == NULL || table == NULL) return;

	srand(time(NULL));

	int r = 0;
	size_t length = 5;
	size_t step = test_array_size / length;

	if (step < 2) step = 2;

	for (size_t i = 0; i < test_array_size; ++i) {
		if (i >= step) {
			++length;
			step += step;
		}

		test_s *test = &(test_array[i]);
		r = test_s_configure_length(test, length);
		
		if (r == 0) {
                        t_r->successes += 1;
                } else {
                        t_r->failures += 1;
                }

		r = h_table_insert(table, (void *)test, hash, test_s_compare);
		
		if (r == 0) {
                        t_r->successes += 1;
                } else {
                        t_r->failures += 1;
                }
	}
}

void h_table_print(h_table *table) {
	if (table == NULL) {
		printf("table is NULL\n");
		return;
	}

	if (table->buckets == NULL) {
                printf("table buckets are NULL\n");
                return;
        }

	size_t max = 0;
	for (size_t i = 0; i < table->size; ++i) {
		size_t m = 0;
		s_list *head = table->buckets[i];
		
		while (head != NULL) {
			head = head->next;
			++m;
		}
		
		if (m > max) max = m;
	}

	printf("table: { size: %i, max_size_of_buckets: %i }\n", (int)table->size, (int)max);
}

void h_table_print_bucket(h_table *table, size_t index) {
	if (table == NULL) {
                printf("table is NULL\n");
                return;
        }

	if (table->buckets == NULL) {
                printf("table buckets are NULL\n");
                return;
        }

	if (index >= table->size) {
		printf("invalid index for buckets\n");
                return;
        }

	s_list *head = table->buckets[index];
        
	if (head == NULL) {
		printf("table bucket %i is NULL\n", (int)index);
		return;
	}

	printf("table bucket %i: ", (int)index);
        while (head != NULL) {
		test_s_print(head->element);
                head = head->next;
	}

	printf("\n");
}


/**
 * test functions
 */

void insertion_search_removal_test(
	h_table *table,
	size_t (*hash)(void *),
	size_t length,
	test_result *t_r) {

	if (length > 9) length = 9;

	test_s u;
	test_s v;

	int r = test_s_configure_length(&u, length);
	
	if (r == 0) {
                t_r->successes += 1;
                console_set_green();
                printf("element configured\n");
                console_set_white();
        } else {
                t_r->failures += 1;
                console_set_red();
                printf("element not configured\n");
                console_set_white();
        }

	for (size_t i = 0; i <= length; ++i)
		v.s[i] = u.s[i];

	r = h_table_insert(table, (void *)(&u), hash, test_s_compare);

	if (r == 0) {
                t_r->successes += 1;
                console_set_green();
		printf("element inserted: %s\n", u.s);
		console_set_white();
	} else {
                t_r->failures += 1;
                console_set_red();
		printf("element not inserted: %s\n", u.s);
                console_set_white();
        }
	
	r = h_table_contains(table, (void *)(&v), hash, test_s_compare);

	if (r == 0) {
		t_r->successes += 1;
                console_set_green();
		printf("element found: %s\n", v.s);
		console_set_white();
	} else {
		t_r->failures += 1;
                console_set_red();
		printf("element not found: %s\n", v.s);
		console_set_white();
	}

	void *element = h_table_remove(table, (void *)(&v), hash, test_s_compare);

	if (element != NULL) {
		t_r->successes += 1;
                console_set_green();
		printf("element removed: ");
		test_s_print(element);
		printf("\n");
		console_set_white();
	} else {
		t_r->failures += 1;
                console_set_red();
		printf("element not removed\n");
		console_set_white();
	}
}

void combination_test(
	size_t size,
	size_t (*hash)(void *),
	char *hash_name,
	int test_number,
	test_result *t_r) {

	printf("\ntable creation, insertion with %s hash function, search, removal and destruction test %i\n",
		hash_name, test_number);

	size_t test_array_size = size;
	test_s *test_array = malloc(test_array_size * sizeof (test_s));

	if (test_array == NULL) {
		printf("test array creation failure\n");
                return;
	}

	h_table *table = h_table_create(size);

	if (table == NULL) {
		printf("table creation failure\n");
		free(test_array);
		return;
	} else {
		printf("table created\n");
	}

	h_table_populate_rand(test_array, test_array_size, table, hash, t_r);
	printf("table insertion complete\n");
	h_table_print(table);
	insertion_search_removal_test(table, hash, 7, t_r);
	h_table_destroy(&table);
	printf("table destroyed\n");
	h_table_print(table);
	free(test_array);
	printf("\n");
}

void insertion_removal_stress_test_a(
	size_t size,
	size_t multiplier,
        size_t (*hash)(void *),
	char *hash_name,
	int test_number,
        test_result *t_r) {

	printf("\ntable insertion with %s hash function and removal stress test %i\n",
                hash_name, test_number);

        size_t test_array_size = size * multiplier;
        test_s *test_array = malloc(test_array_size * sizeof (test_s));

        if (test_array == NULL) {
                printf("test array creation failure\n");
                return;
        }

        h_table *table = h_table_create(size);

        if (table == NULL) {
                printf("table creation failure\n");
                free(test_array);
                return;
        } else {
                printf("table created\n");
        }

	h_table_populate_rand(test_array, test_array_size, table, hash, t_r);
        printf("table insertion complete\n");
	
	printf("test array: ");
	for (size_t i = 0; i < test_array_size; ++i)
		printf("%s ", test_array[i].s);

	printf("\n");
        
	h_table_print(table);

	for (size_t i = 0; i < table->size; ++i)
		h_table_print_bucket(table, i);

	size_t half = test_array_size / 2;

	for (size_t i = 0; i <= half; ++i) {
		test_s *test = &(test_array[i]);
		void *element = h_table_remove(table, (void *)test, hash, test_s_compare);

	        if (element != NULL) {
        	        t_r->successes += 1;
        	} else {
                	t_r->failures += 1;
        	}
	}

	for (size_t i = test_array_size - 1; i > half; --i) {               
                test_s *test = &(test_array[i]);
                void *element = h_table_remove(table, (void *)test, hash, test_s_compare);

                if (element != NULL) {
                        t_r->successes += 1;
                } else {
                        t_r->failures += 1;
                }
        }
	
	printf("table removal complete\n");
	
	for (size_t i = 0; i < table->size; ++i)  
                h_table_print_bucket(table, i);

	h_table_destroy(&table);
        printf("table destroyed\n");
        h_table_print(table);
        free(test_array);
        printf("\n");
}

void insertion_removal_stress_test_b(
	size_t size,
	size_t multiplier,
        size_t (*hash)(void *),
	char *hash_name,
	int test_number,
        test_result *t_r) {

	printf("\ntable insertion with %s hash function and removal stress test %i\n",
                hash_name, test_number);

        size_t test_array_size = size * multiplier;
        test_s *test_array = malloc(test_array_size * sizeof (test_s));

        if (test_array == NULL) {
                printf("test array creation failure\n");
                return;
        }

        h_table *table = h_table_create(size);

        if (table == NULL) {
                printf("table creation failure\n");
                free(test_array);
                return;
        } else {
                printf("table created\n");
        }

	h_table_populate_rand(test_array, test_array_size, table, hash, t_r);
        printf("table insertion complete\n");
	
	printf("test array: ");
	for (size_t i = 0; i < test_array_size; ++i)
		printf("%s ", test_array[i].s);

	printf("\n");
        
	h_table_print(table);

	for (size_t i = 0; i < table->size; ++i)
		h_table_print_bucket(table, i);

	size_t half = test_array_size / 2;

	for (size_t i = test_array_size - 1; i > half; --i) {               
                test_s *test = &(test_array[i]);
                void *element = h_table_remove(table, (void *)test, hash, test_s_compare);

                if (element != NULL) {
                        t_r->successes += 1;
                } else {
                        t_r->failures += 1;
                }
        }
	
	for (size_t i = 0; i <= half; ++i) {
		test_s *test = &(test_array[i]);
		void *element = h_table_remove(table, (void *)test, hash, test_s_compare);

	        if (element != NULL) {
        	        t_r->successes += 1;
        	} else {
                	t_r->failures += 1;
        	}
	}

	printf("table removal complete\n");
	
	for (size_t i = 0; i < table->size; ++i)  
                h_table_print_bucket(table, i);

	h_table_destroy(&table);
        printf("table destroyed\n");
        h_table_print(table);
        free(test_array);
        printf("\n");
}

void creation_destruction_test_0(test_result *t_r) {
	combination_test(BOUNDARY_0, test_s_hash_xor8, "xor8", 0, t_r);
}

void creation_destruction_test_1(test_result *t_r) {
	combination_test(BOUNDARY_0, test_s_hash_adler32, "adler32", 1, t_r);
}

void creation_destruction_test_2(test_result *t_r) {
	combination_test(BOUNDARY_0, test_s_hash_crc32, "crc32", 2, t_r);
}

void creation_destruction_test_3(test_result *t_r) {
	combination_test(BOUNDARY_0, test_s_hash_djb2, "djb2", 3, t_r);
}

void creation_destruction_test_4(test_result *t_r) {
	combination_test(BOUNDARY_0, test_s_hash_sdbm, "sdbm", 4, t_r);
}

void insertion_removal_stress_test_5(test_result *t_r) {
	insertion_removal_stress_test_a(1, 5, test_s_hash_adler32, "adler32", 5, t_r);
}

void insertion_removal_stress_test_6(test_result *t_r) {
        insertion_removal_stress_test_a(1, 5, test_s_hash_crc32, "crc32", 6, t_r);
}

void insertion_removal_stress_test_7(test_result *t_r) {
	insertion_removal_stress_test_b(1, 5, test_s_hash_djb2, "djb2", 7, t_r);
}

void insertion_removal_stress_test_8(test_result *t_r) {
        insertion_removal_stress_test_b(1, 5, test_s_hash_sdbm, "sdbm", 8, t_r);
}


/**
 * main
 */

int main(int argc, char **argv) {
	void (*tests[9])(test_result *) = {
		creation_destruction_test_0,
		creation_destruction_test_1,
		creation_destruction_test_2,
		creation_destruction_test_3,
		creation_destruction_test_4,
		insertion_removal_stress_test_5,
		insertion_removal_stress_test_6,
		insertion_removal_stress_test_7,
		insertion_removal_stress_test_8
	};

	run_tests_display_results(argc, argv, tests, 9);

	return 0;
}

