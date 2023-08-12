make_test:
	gcc -o h_table_test.out -I ../headers \
	../core/s_list.c ../core/h_table.c ../core/hash_helpers.c \
	test_s.c general_test_helpers.c h_table_test.c
