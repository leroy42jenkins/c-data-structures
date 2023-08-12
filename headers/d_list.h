#ifndef D_LIST_H
#define D_LIST_H


#include <stdlib.h>


typedef struct d_list_node_t {
	void *element;
	struct d_list_node_t *front;
	struct d_list_node_t *back;
} d_list_node;

typedef struct d_list_t {
	size_t size;
	d_list_node *front;
	d_list_node *back;
} d_list;

d_list * d_list_create();

void * d_list_peek_front(d_list *);

void * d_list_peek_back(d_list *);

int d_list_push_front(d_list *, void *);

int d_list_push_back(d_list *, void *);

void * d_list_pop_front(d_list *);

void * d_list_pop_back(d_list *);

void d_list_destroy(d_list **);


#endif

