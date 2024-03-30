make_test:
	gcc -Wall -o bin_tree_test.out -I ../headers \
	../core/bin_tree.c test_0.c general_test_helpers.c bin_tree_test.c
