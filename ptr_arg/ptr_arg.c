#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <unistd.h>
#include <stdlib.h>
#include <getopt.h>
#include <errno.h>


static void usage(char *cmd)
{
	printf("Usage: %s [OPTION]...\n"
			"-h, --help		help\n"
			"-t, --test=#	test arg, # 1 mean char ptr, 2 mean char second ptr\n", cmd);	
}

static long parse_long(const char *str, int *err)
{
	long val;
	char *endptr;
	
	errno = 0;
	val = strtol(str, &endptr, 0);

	if (errno != 0 || *endptr != '\0')
		*err = -1;
	else
		*err = 0;

	return val;
}

static void char_ptr_arg(char *str)
{
	str = malloc(100);	
	printf("func: %s, str addr: %p\n", __func__, str);
}


static void char_second_ptr_arg(char **str)
{
	*str = malloc(100);	
	printf("func: %s, str addr: %p, *str addr: %p\n", __func__, str, *str);
}

int main(int argc,  char **argv)
{
	char *str_ptr = NULL;
	int tmp, err, c;
	int option_index;
	int test_type;
	const char short_options[] = "ht:";

	static const struct option long_options[] = {
		{"help", 0, 0, 'h'},
		{"test", 1, 0, 't'},
		{0, 0, 0, 0}
	};	
	
	while ((c = getopt_long(argc, argv, short_options, long_options, &option_index)) != -1) {
		switch (c) {
			case 'h':
				usage(argv[0]);
				return 0;
			case 't':
				test_type = parse_long(optarg, &err);
				if (err < 0) {
					printf("invalid test type '%s'\n", optarg);
					return 1;
				}
		}
	}
	
	if (test_type == 1) {
		char_ptr_arg(str_ptr);
		printf("str_ptr addr: %p\n", str_ptr);
		if (str_ptr == NULL) {
			printf("str_ptr not malloc success\n");
		} else {
			strcpy(str_ptr, "hello malloc");
			printf("str_ptr malloc success, address: %p\n", str_ptr);
			free(str_ptr);
		}
	} else if (test_type == 2) {
		char_second_ptr_arg(&str_ptr);
		printf("str_ptr addr: %p\n", str_ptr);
		if (str_ptr == NULL) {
			printf("str_ptr not malloc success\n");
		} else {
			strcpy(str_ptr, "hello malloc");
			printf("str_ptr malloc success, str_ptr addr: %p, *str_ptr addr: %p\n", str_ptr, *str_ptr);
			free(str_ptr);
		}
	} else {
		usage(argv[0]);
	}
	
	return 0;	
}
