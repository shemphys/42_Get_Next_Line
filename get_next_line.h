#ifndef GET_NEXT_LINE
# define GET_NEXT_LINE

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
//creo que me sobra alguna lib: QUITAR LAS QUE ME SOBREN

/* creamos la estructura */
typedef struct s_list
{
	char			*str_buf;
	struct s_list	*next;
}					t_list;

#endif