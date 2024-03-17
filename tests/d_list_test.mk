make_test:
	gcc -Wall -o d_list_test.out -I ../headers \
	../core/d_list.c test_0.c general_test_helpers.c d_list_test.c
