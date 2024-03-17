#include "d_list.h"


d_list * d_list_create() {
	d_list *list = malloc(sizeof (d_list));
	if (list == NULL) return NULL;
	list->size = 0;
	list->front = NULL;
	list->back = NULL;
	return list;
}

void * d_list_peek_front(d_list *list) {
	return list == NULL || list->front == NULL
		? NULL
		: list->front->element;
}

void * d_list_peek_back(d_list *list) {
	return list == NULL || list->back == NULL
		? NULL
		: list->back->element;
}

int d_list_push_front(d_list *list, void *element) {
	if (list == NULL) return -1;

	d_list_node *node = malloc(sizeof (d_list_node));

	if (node == NULL) return -1;

	node->element = element;
	node->front = NULL;

	if (list->size == 0) {
		node->back = NULL;
		list->front = node;
		list->back = node;
	} else {
		node->back = list->front;
		list->front->front = node;
		list->front = node;
	}

	list->size += 1;
	return 0;
}

int d_list_push_back(d_list *list, void *element) {
	if (list == NULL) return -1;

	d_list_node *node = malloc(sizeof (d_list_node));

	if (node == NULL) return -1;

	node->element = element;
	node->back = NULL;

	if (list->size == 0) {
		node->front = NULL;
		list->front = node;
		list->back = node;
	} else {
		node->front = list->back;
		list->back->back = node;
		list->back = node;
	}

	list->size += 1;
	return 0;
}

void * d_list_pop_front(d_list *list) {
	if (list == NULL || list->size == 0) return NULL;

	void *element = NULL;

	if (list->size == 1) {
		element = list->front->element;
		free(list->front);
		list->front = NULL;
		list->back = NULL;
	} else {
		element = list->front->element;
		d_list_node *t = list->front->back;
		free(list->front);
		t->front = NULL;
		list->front = t;
	}

	list->size -= 1;
	return element;
}

void * d_list_pop_back(d_list *list) {
	if (list == NULL || list->size == 0) return NULL;

	void *element = NULL;

	if (list->size == 1) {
		element = list->back->element;
		free(list->back);
		list->back = NULL;
		list->front = NULL;
	} else {
		element = list->back->element;
		d_list_node *t = list->back->front;
		free(list->back);
		t->back = NULL;
		list->back = t;
	}

	list->size -=1;
	return element;
}

void d_list_destroy(d_list **list) {
	if (list == NULL || *list == NULL) return;
	
	while ((*list)->size > 0)
		d_list_pop_front(*list);
	
	free(*list);
	*list = NULL;
}

