#include "get_next_line.h"

t_list *create_new_node(int fd)
{
	t_list	*new;
	int		char_read;

	new = malloc(sizeof(t_list));
	if (!new)
		return (NULL);
	char_read = read(fd, new->buffer, BUFFER_SIZE);
	if (!char_read)
	{
		free(new);
		return (NULL);
	}
	new->buffer[BUFFER_SIZE] = '\0';
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

	if (line == NULL)
		return (NULL);
	aux = line;
	while (aux != NULL)
	{
		if (*aux == '\n')
			return (1);
		aux++;
	}
	return (0);//no hay saltos de línea
}

//necesito saber cómo de grande será output_line
int ft_len_to_newline(t_list *head, int fd)
{
	int	i;
	int	len;
	//creo que debería crear AUX para no perder la cabeza xD

	if (head == NULL)
		return (0);
	len = 0;
	while (head)
	{
		i = 0;
		while (head->buffer[i] != '\0')
		{
			if (head->buffer[i] == '\n')
			{
				len++;
				return (len);
			}
			i++;
			len++;
		}
		head = head->next;
	}
	return (len);//no sé si debería meterle un +1 xD
}

//concatena: va guardando la info en output_line + update ->next + free()


char *get_next_line(int fd)
{
	static t_list	*head;//static holdea la info cuanto dure el main
	t_list	*aux;
	char	*output_line;

	head = NULL;
	if (read(fd, 0, 0) || BUFFER_SIZE <= 0 || fd < 0)
		return (NULL);
	//creamos lista y vamos almacenando
	while (newlinefinder(aux) == 0)
		aux = get_or_add_node(&head, fd);//y busco '\n'
	//si salimos de este bucle -> aux contiene '\n'
	
	output_line = ft_concatena()



	//aquí tengo que proteger que *head o fd vayan con condimento.
	//FREE
}



//INSTRUCCIONES
// -> liberar memoria

// encontrar '\n'