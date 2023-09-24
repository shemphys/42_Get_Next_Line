//#include "get_next_line.h"
////////////////////////////////////////////////
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

////////////////////////////////////////////////
t_list *create_new_node(int fd)
{
	t_list	*new;
	int		char_read;

	new = malloc(sizeof(t_list));
	if (!new)
		return (NULL);
	char_read = read(fd, new->buffer, BUFFER_SIZE);
	new->buffer[BUFFER_SIZE] = '\0';
	if (!char_read)
	{
		free(new);
		return (NULL);
	}
	new->next = NULL;
	return (new);
}

t_list *get_or_add_node(t_list **head, int fd)
{//buscar si existe por el identificador fd. Si no existe: crear y añadir
	t_list	*aux;
	t_list	*prev;
	t_list	*new;

	aux = *head;
	prev = NULL;
	while (aux)
	{
		prev = aux;
		aux = aux->next;
	}
	new = create_new_node(fd);//falta añadir la línea.
	if (!new)
		return (NULL);
	if (prev)//necesito que prev apunte a NULL
		prev->next = new;
	else//porque sino significa que solo había un nodo: head
		*head = new;
	return (new);
}

//bucle que checkea si existe '\n' en el buffer
int newlinefinder(char *line)
{
	char	*aux;

	//creo que aquí no hay nada que proteger, la verdad
	//if (line == NULL)
	//	return ;
	aux = line;
	while (aux != '\0')
	{
		if (*aux == '\n')
			return (1);
		aux++;
	}
	return (0);//no hay saltos de línea
}

//necesito saber cómo de grande será output_line
int ft_len_until_newline(t_list *head)
{
	int		i;
	int		len;
	t_list	*aux;
	//creo que debería crear AUX para no perder la cabeza xD

	aux = head;
	len = 0;
	if (head == NULL)
		return (0);
	while (aux)
	{
		i = 0;
		while (aux->buffer[i] != '\0')
		{
			if (aux->buffer[i] == '\n')
			{
				len++;
				return (len);
			}
			i++;
			len++;
		}
		aux = aux->next;
	}
	return (len);//no sé si debería meterle un +1 xD
}

//borrar nodos hasta '\n' inclusive

char *get_next_line(int fd)
{
	static t_list	*head;//static holdea la info cuanto dure el main
	t_list			*aux;
	char			*output_line;
	int				i;
	int				b;
	char			*aux_line;

	head = NULL;
	if (read(fd, 0, 0) || BUFFER_SIZE <= 0 || fd < 0)
		return (NULL);
	//creamos lista y vamos almacenando
	aux = get_or_add_node(&head, fd);
	while (newlinefinder(aux->buffer) == 0)
		aux = get_or_add_node(&head, fd);//y busco '\n'
	//si salimos de este bucle -> aux contiene '\n'
	
	i = ft_len_until_newline(head);//no es para esto, pero la reutilizo xD
	output_line = malloc(i + 1);
	aux_line = malloc(i + 1);
	if (!output_line)
		return (NULL);
	output_line[i] = '\0';
	i = 0;
	//creo la línea y voy borrando los nodos
	//OJO!! QUE CON ESTO BORRO EL NODO ÚLTIMO QUE NO SIEMPRE
	while (output_line[i] != '\0')
	{
		aux = head;
		b = 0;
		while (head->buffer[b] != '\0')
		{
			if (head->buffer[b] == '\n')//aquí termina el NODO TAMBIÉN
			{
				output_line[i] = '\n';
				while (head->buffer[b] != '\0')
				{
					*aux_line = head->buffer[b];
					b++;
					aux_line++;
				}
				free(aux);
				return (output_line);
			}
			output_line[i] = head->buffer[b];
			b++;
			i++;
		}
			head = head->next;
			free(aux);
	}
	return (NULL);//tiene que terminar con algo siempre. Pos esto mismo x ejemplo xD
}

/* ----------------------------------------------- */
/* ----------------------------------------------- */
/* ----------------------------------------------- */

int main (void)
{
	int fd = open("subject.txt", O_RDONLY);
	printf("%s", get_next_line(fd));
	close(fd);
}