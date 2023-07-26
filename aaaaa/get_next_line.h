#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>

# include <stdlib.h>
# include <stdio.h>//TODO

typedef struct		s_list
{
	char			*str_buff;
	struct s_list	*next;
}                   t_list;

char	*get_next_line(int fd);
void	crete_list(t_list **list, int fd);
int		found_newline(t_list *list);

#endif