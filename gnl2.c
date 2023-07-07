//Las variables locales se destruyen. Los punteros pueden sobrevivir. (?)
// Miguel añadió un OPEN_MAX para manejar un error: el máximo que puede abrir open()

#include <unistd.h>
#include <stdlib.h>//malloc(), free()
#include <stdio.h>//printf()
#include <fcntl.h>//open(), O_RDONLY

#ifndef BUFFER_SIZE
#define BUFFER_SIZE 7
#endif

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

char *get_next_line(int fd)
{
	static char	*stash;
	char		*line;
	char		buffer[BUFFER_SIZE + 1];//un array normalito, sin más
	int			i;
	int			bytes_read;

	i = 0;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);

	bytes_read = read(fd, buffer, BUFFER_SIZE);
	if (bytes_read < 0)
		return (NULL);

	buffer[bytes_read] = '\0';

/* 	stash = malloc(sizeof(char) * bytes_read + 1);
	if (!stash)
		return (NULL); */
	while (i < bytes_read && buffer[i] != '\0')
	{
		stash[i] = buffer[i];
		i++;
	}
	stash[i] = '\0';
	//ahora que meter stash en line hasta el '\n'
	
	line = malloc(sizeof(char) * ft_strlen(stash) + 1);
	if (!line)
	{
		free(stash);
		return (NULL);
	}

	i = 0;
	while (stash[i] != '\0' && stash[i] != '\n')
	{
		line[i] = stash[i];
		i++;
	}
	line[i] = '\0';
	free(stash);//esto habrá que quitarlo después que no hay que liberar esta memoria
				//de hecho habrá que limpiar el trozo posterior a \n
	return (line);
}

int main(void)
{
	char	*aux;
	int		fd = open("C:/Users/mykje/Documents/GitHub/42_Get_Next_Line/testeo", O_RDONLY);

	aux = get_next_line(fd);
	printf("%s", aux);
	free(aux);
	return(0);
}
//MOVIDAS
// si trozo que leo justo termina en el salto de línea
// al mostrarlo por por pantalla No muestra nada.