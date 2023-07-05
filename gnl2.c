//Las variables locales se destruyen. Los punteros pueden sobrevivir. (?)

#include <unistd.h>
#include <stdlib.h>//malloc(), free()
#include <stdio.h>//printf()
#include <fcntl.h>//open(), O_RDONLY

#ifndef BUFFER_SIZE
#define BUFFER_SIZE 7
#endif

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
		if (buffer[i] == '\n')//objetivo: almacenar todo el bufer dentro de stash, pero salir del bucle
			{
				while (i < BUFFER_SIZE && buffer[i])
				{
					stash[i] = buffer[i];
					i++;
				}
				break;//quizás puedo meter aquí el return de una 
			}
		stash[i] = buffer[i];
		i++;
	}

	return(stash);
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