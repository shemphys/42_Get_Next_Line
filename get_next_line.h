#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

#include <stdlib.h>
#include <unistd.h>

#ifndef BUFFER_SIZE
#define BUFFER_SIZE 42
#endif

typedef struct s_fragment {
	char *data;
	size_t len;
	struct s_fragment *next;
} t_fragment;

#endif