#ifndef GET_NEXT_LINE
# define GET_NEXT_LINE

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

# include <fcntl.h>
# include <stdlib.h>//malloc, free
# include <unistd.h>
# include <stdio.h>
//creo que me sobra alguna lib: QUITAR LAS QUE ME SOBREN

typedef struct		s_list
{
	char			buffer[BUFFER_SIZE + 1];
	struct s_list	*next;
}					t_list;
//tengo que entender mejor por qué es importante el orden de estas funciones
//get_or_add_node si está debajo de get_next_line da error
t_list	*get_or_add_node(t_list **head, int fd);
char	*get_next_line(int fd);
t_list	*create_new_node(int fd);


#endif