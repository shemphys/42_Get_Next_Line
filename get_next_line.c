//#include "get_next_line.h"

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

t_fragment *fragment_create(char *data, size_t len)
{
	t_fragment *frag = malloc(sizeof(t_fragment));
	if (!frag)
		return NULL;
	frag->data = data;
	frag->len = len;
	frag->next = NULL;
	return (frag);
}

void free_fragments(t_fragment *head)
{
	t_fragment *tmp;
	while (head)
	{
		tmp = head;
		head = head->next;
		free(tmp);
	}
}

char *get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE + 1];
	char		*line;
	ssize_t		read_bytes;
	size_t		i;
	size_t		j;
	size_t		buffer_len;
	t_fragment *head = NULL, *tail = NULL, *frag;
	size_t		line_len;

	*line = NULL;
	i = 0;
	j = 0;
	buffer_len = 0;
	line_len = 0;
	while (1)
	{
		while (buffer_len < BUFFER_SIZE && buffer[buffer_len] != '\n')
		{
			read_bytes = read(fd, buffer + buffer_len, BUFFER_SIZE - buffer_len);
			if (read_bytes < 0) {
				free(line);
				free_fragments(head);
				return NULL;
			}
			buffer_len += read_bytes;

			if (read_bytes == 0)
				break ;
		}

		buffer[buffer_len] = '\0';

		i = 0;
		while (i < buffer_len && buffer[i] != '\n') i++;

		if (i < buffer_len && buffer[i] == '\n' || read_bytes == 0)
		{
			frag = fragment_create(buffer, i);
			if (!frag) {
				free(line);
				free_fragments(head);
				return NULL;
			}

			if (!head)
				head = frag;
			if (tail)
				tail->next = frag;
			tail = frag;
			line_len += frag->len;

			if (i < buffer_len && buffer[i] == '\n')
			{
				if (line_len == 0)
				{
					line = malloc(1 * sizeof(char));
					if (!line)
					{
						free_fragments(head);
						return NULL;
					}
					*line = '\0';
					return line;
				}
				line = malloc((line_len + 1) * sizeof(char));
				if (!line)
				{
					free_fragments(head);
					return NULL;
				}

				char *ptr = line;
				while (head)
				{
					frag = head;
					j = 0;
					while (j < frag->len)
					{
						*(ptr++) = frag->data[j];
						j++;
					}
					head = frag->next;
					free(frag);
				}
				*ptr = '\0';

				j = 0;
				while (buffer[i] != '\0')
				{
					buffer[j] = buffer[i];
					j++; i++;
				}
				buffer_len -= i;

				return line;
			}

			j = 0;
			while (buffer[i] != '\0')
			{
				buffer[j] = buffer[i];
				j++; i++;
			}
			buffer_len -= i;
		}

		if (read_bytes == 0)
		{
			free_fragments(head);
			return NULL;
		}
	}
}


