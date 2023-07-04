
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
	while (!file_check || !buffer)//podria ahorrarme una línea haciendo modificando este paréntesis?
	{//		(!read(fd, &buffer, BUFFER_SIZE) || !buffer)	Esto hace la asignación en buffer?? puedo usarlo??
		file_check = read(fd, &buffer, BUFFER_SIZE);//esto hay que hacerlo bucle, o solo leeré BUFFER_SIZE bytes.
		if (!file_check || !buffer)
			return (NULL);
		while (buffer[i] != '\n' || !buffer[i])	//ahora vamos a comprobar que no haya saltos de línea
			i++;
		if (i == ft_strlen(buffer))//si no existen saltos de línea, meto todo el buffer en paahora
			ft_strjoin(paahora, buffer);
		else
		{
			ft_strncpy(paahora + ft_strlen(paahora), buffer, i);//esto concatenará i char de buffer en paahora.
			paahora[ft_strlen + 1] = '\0';
			//ahora tengo que rellenar *paluego con lo que sobre que siga conteniendo buffer
			if (i < BUFFER_SIZE && buffer[BUFFER_SIZE] != '\0')//la 2 condición es por si ya hemos leído todo el documento
				ft_strncpy(paluego, buffer[i], BUFFER_SIZE - i);//para copiar desde [i] hasta BUFFER_SIZE - 1
		}
	return (paahora);
	}
}