#ifndef H_TABLE_H
#define H_TABLE_H


#include <stdlib.h>
#include <stdio.h>


#include "s_list.h"


/**
 * hash table struct and functions
 */

typedef struct h_table_t {
	size_t size;
	s_list **buckets;
} h_table;

h_table * h_table_create(size_t);

int h_table_insert(h_table *, void *, size_t (*)(void *), int (*)(void *, void *));

int h_table_contains(h_table *, void *, size_t (*)(void *), int (*)(void *, void *));

void * h_table_remove(h_table *, void *, size_t (*)(void *), int (*)(void *, void *));

void h_table_destroy(h_table **);


#endif

