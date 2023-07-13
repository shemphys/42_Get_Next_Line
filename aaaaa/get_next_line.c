#include "get_next_line.h"

void	crete_list(t_list **list, int fd)
{
	int		char_read;
	char	*buff;

	while (!found_newline(*list))
	{
		buff = malloc(BUFFER_SIZE + 1);
		if (!buff)
			return;
		char_read = read(fd, buf, BUFFER_SIZE);
		if (!char_read)
		{
			free(buff);
			return ;
		}
		buff[char_read] = '\0';
		append(list, buff);
	}
}

char	*get_next_line(fd)
{
	static t_list	*list = NULL;
	char			*next_line;

	if (fd < 0 || BUFFER_SIZE <=0 || read(fd, &next_line, 0) < 0)
		return (NULL);
	create_list(&list, fd);
	if (!list)// NULL == list
		return (NULL);
	next_line = get_line(list);
	polish_list(&list);
	return(next_line);
}


/*
 Uso OPEN_MAX de limits.h para poder capturar tantos fd simultáneamente como sea necesario.
 Inicio la lista enlazada
  que tendrá un puntero static
   (para que no se pierda su valor entre iteraciones)
 Capturo el fd
 Capturo la primera string de tamaño BUFFER_SIZE en el primer nodo
 Compruebo que en esa string no existen 

 
 LAS LISTAS NECESITAN MUCHAS COSAS
 - declaración de su estructura (*.h)
 - inicialización (nodo cabeza + nodo final (que son el mismo al principio))
 - creación de nuevos nodos
 - limpieza de nodos

*/