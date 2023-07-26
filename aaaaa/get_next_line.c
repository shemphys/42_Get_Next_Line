#include "get_next_line.h"

void	append(t_list **list, char *buff)
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
		last_node->next = new_node;
	new_node->str_buff = buff;
	new_node->next = NULL;
}

void	create_list(t_list **list, int fd)
{
	int		char_read;
	char	*buff;

	while (!found_newline(*list))//¿por qué para cuando devuelve 1??
	{
		buff = malloc(BUFFER_SIZE + 1);
		if (!buff)
			return ;
		char_read = read(fd, buff, BUFFER_SIZE);
		if (!char_read)
		{
			free(buff);
			return ;
		}
		buff[char_read] = '\0';//si usase BUFFER_SIZE como punto donde poner \0
		//habría veces que quedaría mierda entre la string y el nulo.
		append(list, buff);
	}
}

char	*get_next_line(int fd)
{
	static t_list	*list;//nodo cabeza
	char			*next_line;

	list = NULL;//está bien hacer esto porque a lo mejor en el if se va a tomar por culo y es un static
	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
	//compruebo que el fd está bien, que el bs está bien y que podemos leer.
	//ssize_t read(int fd, void *buf, size_t count);
	//como solo puedo leer 1 vez, cada cosa, count debe ser 0
		return (NULL);
	create_list(&list, fd);
	if (!list)
		return (NULL);
	next_line = get_line(list);
	polish_list(&list);
	return(next_line);
}


/*
 Uso OPEN_MAX de limits.h para poder capturar tantos fd simultáneamente como sea necesario. [bonus]
 
 Inicio la lista enlazada
  que tendrá un puntero static
   (para que no se pierda su valor entre iteraciones)
 Capturo el fd
 Capturo la primera string de tamaño BUFFER_SIZE en el primer nodo
 Compruebo que en esa string no existe \n
  Si no existe: crear nodo, guardar string, comprobar si existe \n
  Si sí existe:
	- guardar todas las strings de los nodos en un array o puntero que luego devolveremos
		el \n inclusive
	- limpiar todas la memoria que hemos devuelto
	- nuestra lista quedará con: nodo cabeza, nodo con el trozo de string restante, nodo cola
 Repetir hasta el final del archivo.
 

 LAS LISTAS NECESITAN MUCHAS COSAS
 - declaración de su estructura (*.h)
 - inicialización (nodo cabeza + nodo final (que son el mismo al principio))
 - creación de nuevos nodos
 - limpieza de nodos

ale, pogramar crack! :D
*/

/*
 La diferencia entre bonus y nobonus es que en bonus sabemos que habrá
  más fd, de forma que tendremos que crear instancias distintas según el fd.
 Usaremos la librería limits.h y OPEN_MAX, porque dependiendo del sistema
  éste tendrá un límite u otro. Es más óptimo esto que poner un número "a lo loco"
*/