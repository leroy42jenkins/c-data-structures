#include "h_table.h"


h_table * h_table_create(size_t size) {
	h_table *table = malloc(sizeof (h_table));

	if (table == NULL) return NULL;

	table->buckets = malloc(size * sizeof (s_list *));

	if (table->buckets == NULL) {
		free(table);
		return NULL;
	}

	table->size = size;

	for (size_t i = 0; i < size; ++i) {
		table->buckets[i] = NULL;
	}

	return table;
}

int h_table_insert(h_table *table, void *element, size_t (*hash)(void *), int (*compare)(void *, void *)) {
	if (table == NULL || table->size < 1) return -1;

	size_t h_value = hash(element);
	size_t index = h_value % table->size;

	if (table->buckets[index] == NULL) {
		s_list *list = s_list_create(element);
		if (list == NULL) return -1;
		table->buckets[index] = list;
		return 0;
	}

	return s_list_push(&(table->buckets[index]), element);
}

int h_table_contains(h_table *table, void *element, size_t (*hash)(void *), int (*compare)(void *, void *)) {
	if (table == NULL || table->size < 1) return -1;

	size_t h_value = hash(element);
	size_t index = h_value % table->size;

        s_list *current = table->buckets[index];

        while (current != NULL) {
                int r = compare(element, current->element);
                if (r == 0) return 0;
		current = current->next;
        }

	return -1;
}

void * h_table_remove(h_table *table, void *element, size_t (*hash)(void *), int (*compare)(void *, void *)) {
	if (table == NULL || table->size < 1) return NULL;

	size_t h_value = hash(element);
	size_t index = h_value % table->size;
	
	s_list *last = NULL;
	s_list *current = table->buckets[index];

        while (current != NULL) {
                int r = compare(element, current->element);   
                
		if (r == 0) {
			void *e = current->element;

			if (last == NULL) {
				if (current->next == NULL) {
					table->buckets[index] = NULL;
				} else {
					table->buckets[index] = current->next;
				}
			} else {
				last->next = current->next;
			}

			current->next = NULL;
			s_list_destroy(&current);
			return e;
		}

		last = current;
		current = current->next;
        }

	return NULL;
}

void h_table_destroy(h_table **table) {
	if (table == NULL || *table == NULL) return;

	if ((*table)->buckets != NULL) {
		size_t size = (*table)->size;
		for (size_t i = 0; i < size; ++i) {
			s_list **list = &((*table)->buckets[i]);
			s_list_destroy(list);
		}

		free((*table)->buckets);
	}
	
	free(*table);
	*table = NULL;
}

