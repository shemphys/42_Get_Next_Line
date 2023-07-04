
#include <unistd.h>
#include <unistd.h>

#ifndef BUFFER_SIZE
#define BUFFER_SIZE 42
#endif

//la función open() devuelve un int, que es lo que me van a pasar.

char *get_next_line(int fd)
{
	static char	*paluego;//lo que me guardo para la siguiente iterancia jiji
	char		*paahora;//lo que devuelvo en cada iterancia
	int			file_check;//compruebo que la asignación se haya hecho bien
	char		buffer[BUFFER_SIZE + 1];//un buffer no es más que un array?...vaya decepción
	int			i;//contador para recorrer el array buffer
	
	i = 0;
	if (!fd)
		return (NULL);
	while (!file_check || !buffer)
	{
		file_check = read(fd, &buffer, BUFFER_SIZE);//estoy hay que hacerlo bucle, o solo leeré BUFFER_SIZE bytes.
		if (!file_check || !buffer)
			return (NULL);
		ft_strjoin(paahora, buffer);
	}
	//ahora vamos a comprobar que no haya saltos de línea
	while (buffer[i] != '\n' || !buffer[i])
		i++;
	
	
}