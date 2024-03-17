#include "bin_tree.h"


bin_tree * bin_tree_create(void *element) {
    bin_tree *root = malloc(sizeof (bin_tree));
    if (root == NULL) return NULL;
    root->element = element;
    root->left = NULL;
    root->right = NULL;
    return root;
}

bin_tree * bin_tree_insert(bin_tree *node, void *element, int (*compare)(void *a, void *b)) {
    if (node == NULL) return bin_tree_create(element);

    int r = compare(element, node->element);

    if (r < 0) {
        node->left = bin_tree_insert(node->left, element, compare);
        return node;
    } else if (r > 0) {
        node->right = bin_tree_insert(node->right, element, compare);
        return node;
    }

    bin_tree *new_node = bin_tree_create(element);
    if (new_node == NULL) return NULL;
    new_node->left = node->left;
    new_node->right = node->right;
    free(node);
    return new_node;
}

int bin_tree_contains(bin_tree *node, void *element, int (*compare)(void *a, void *b)) {
    if (node == NULL) return -1;

    int r = compare(element, node->element);

    if (r < 0) {
        return bin_tree_contains(node->left, element, compare);
    } else if (r > 0) {
        return bin_tree_contains(node->right, element, compare);
    }

    return 0;
}

bin_tree * bin_tree_remove(bin_tree *node, void *element, int (*compare)(void *a, void *b)) {
    if (node == NULL) return NULL;

    int r = compare(element, node->element);

    if (r < 0) {
        node->left = bin_tree_remove(node->left, element, compare);
        return node;
    } else if (r > 0) {
        node->right = bin_tree_remove(node->right, element, compare);
        return node;
    }

    // TODO: fill in ...
}

bin_tree * bin_tree_destroy(bin_tree *node) {
    if (node == NULL) return NULL;
    node->left = bin_tree_destroy(node->left);
    node->right = bin_tree_destroy(node->right);
    free(node);
    return NULL;
}