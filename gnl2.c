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

	i = 0;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);

	read(fd, buffer, BUFFER_SIZE);

	stash = malloc(sizeof(char) * BUFFER_SIZE + 1);
	while (i < BUFFER_SIZE && buffer[i])
	{
		stash[i] = buffer[i];
		i++;
	}
	stash[i] = '\0';
	//ahora que meter stash en line hasta el '\n'
	
	line = malloc(sizeof(char) * ft_strlen(stash) + 1);
	i = 0;
	while (stash[i] != '\0')
	{
		line[i] = stash[i];
		i++;
	}
	line[i] = '\0';
	free(stash);
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