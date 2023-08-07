#include "get_next_line.h"

int len_to_newline(t_list *list)
{
	int	i;
	int	len;

	if (!list)
		return (0);
	len = 0;
	while (list)
	{
		i = 0;
		while (list->str_buf[i])
		{
			
		}
		
	}
}

char *get_line(t_list *list)
{
	int		str_len;
	char	*next_str;

	if (!list)
		return (NULL);
	str_len = len_to_newline(list);
	/* aaaaaaaaaaaaaaaaa */
}

t_list *find_last_node(t_list *list)
{
	if (!list)
		return (NULL);
	while (list->next)
		list = list->next;
	return (list);
}

void append(t_list **list, char *buffer)
{
	t_list	*new_node;
	t_list	*last_node;

	last_node = find_last_node(*list);
	new_node = malloc(sizeof(t_list));
	if (!new_node)
		return ;
	if (!last_node)
		*list = new_node;
	else
		last_node->new = new_node;
	new_node->str_buf = buffer;
	new_node->next = NULL;
}

int found_newline(t_list *list)//finished
{
	int	i;

	if (!list)
		return (0);
	while (list)
	{
		i = 0;
		while (list->str_vuf[i] && i < BUFFER_SIZE)
		{
			if (list->str_buf[i] == '\n')
				return (1);
			++i;//i++;??
		}
		list = list->next;
	}
	return (0);
}

/* ¿Por qué doble puntero? */
void create_list(t_list **list, int fd)//finished
{
	int		char_read;
	char	*buffer;

	while (!found_newline(*list))
	{
		buffer = malloc(BUFFER_SIZE + 1);
		if (!buffer)
			return ;
		char_read = read(fd, buffer, BUFFER_SIZE);
		if (!char_read)
		{
			free(buffer);
			return ;
		}
		buffer[char_read] =  '\0';
		append(list, buf);
	}
}

char *get_next_line(int fd)
{
	static t_list	*list;//= NULL; creo que no puedo usar esto aquí
	char			*next_line

	*list = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, &next_line, 0) < 0)
		return NULL;
	create_list(&list, fd);
	if (!list)
		return (NULL);
	next_line = get_line(list);
	/* aaaaaaaaaaaa */
}

