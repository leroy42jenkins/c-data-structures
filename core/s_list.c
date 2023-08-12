#include "s_list.h"


s_list * s_list_create(void *element) {
	s_list *list = malloc(sizeof (s_list));
	if (list == NULL) return NULL;
	list->element = element;
	list->next = NULL;
	return list;
}

void s_list_apply(s_list *node, void (*action)(void *)) {
	while (node != NULL) {
		action(node->element);
		node = node->next;
	}
}

int s_list_push(s_list **head, void *element) {
	if (head == NULL || *head == NULL) return -1;
	s_list *node = s_list_create(element);
	if (node == NULL) return -1;
	node->next = *head;
	*head = node;
	return 0;
}

void * s_list_top(s_list *head) {
	return head != NULL ? head->element : NULL;
}

void * s_list_pop(s_list **head) {
	if (head == NULL || *head == NULL) return NULL;
	void *element = (*head)->element;
	s_list *next = (*head)->next;
	free(*head);
	*head = next;
	return element;
}

void s_list_destroy(s_list **head) {
	if (head == NULL) return;

	s_list *next = NULL;
	while (*head != NULL) {
		next = (*head)->next;
		free(*head);
		*head = next;
	}
}

