#ifndef S_LIST_H
#define S_LIST_H


#include <stdlib.h>


/**
 * singly linked list struct and functions
 */

typedef struct s_list_t {
	void *element;
	struct s_list_t *next;
} s_list;

void s_list_apply(s_list *, void (*)(void *));

s_list * s_list_create(void *);

int s_list_push(s_list **, void *);

void * s_list_top(s_list *);

void * s_list_pop(s_list **);

void s_list_destroy(s_list **);


#endif

