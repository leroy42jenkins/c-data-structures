#ifndef BIN_TREE_H
#define BIN_TREE_H


#include <stdlib.h>
#include <stdio.h>


/**
 * binary tree struct and functions
 */

typedef struct bin_tree_t {
    void *element;
	struct bin_tree_t *left;
    struct bin_tree_t *right;
} bin_tree;

bin_tree * bin_tree_create(void *);

bin_tree * bin_tree_insert(bin_tree *, void *, int (*)(void *, void *));

int bin_tree_contains(bin_tree *, void *, int (*)(void *, void *));

void * bin_tree_min(bin_tree *);

void * bin_tree_max(bin_tree *);

bin_tree * bin_tree_remove(bin_tree *, void *, int (*)(void *, void *));

bin_tree * bin_tree_destroy(bin_tree *);


#endif

