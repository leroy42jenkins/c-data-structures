make_test:
	gcc -o s_list_test.out -I ../headers \
	../core/s_list.c test_0.c general_test_helpers.c s_list_test.c
