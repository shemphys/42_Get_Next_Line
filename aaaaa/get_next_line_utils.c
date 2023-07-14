#include "get_next_line.h"

int found_newline(t_list *list)
{
	int	i;

	if (!list)
		return (0);
	while (list)
	{
		i = 0;
		while (list->str_buff[i] && i < BUFFER_SIZE)
		{
			if (list->str_buff[i] == '\n')
				return (1);
			++i;//??? por qué en este sentido??
		}
		list = list->next;
	}
	return (0);
}