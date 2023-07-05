
#include <unistd.h>
#include <unistd.h>
#include <stdio.h>//printf()
#include <stdlib.h>//malloc
#include <string.h>//strncpy

#ifndef BUFFER_SIZE
#define BUFFER_SIZE 42
#endif

////////////////////////UTILS//////////////////////////


int	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	i;
	size_t	j;
	char	*destino;

	j = 0;
	i = 0;
	if (!s1 || s2 == NULL)
		return (NULL);
	destino = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!destino)
		return (NULL);
	while (s1[i] != '\0')
	{
		destino[i] = s1[i];
		i++;
	}
	while (s2[j] != '\0')
	{
		destino[i + j] = s2[j];
		j++;
	}
	destino[i + j] = '\0';
	return (destino);
}
//////////////////////////////////////////////////


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
			strncpy(paahora + ft_strlen(paahora), buffer, i);//esto concatenará i char de buffer en paahora.
			paahora[ft_strlen + 1] = '\0';
			//ahora tengo que rellenar *paluego con lo que sobre que siga conteniendo buffer
			if (i < BUFFER_SIZE && buffer[BUFFER_SIZE] != '\0')//la 2 condición es por si ya hemos leído todo el documento
				strncpy(paluego, buffer[i], BUFFER_SIZE - i);//para copiar desde [i] hasta BUFFER_SIZE - 1
		}
	return (paahora);
	}
}

int main(void)
{
	int		fd = read("C:/Users/mykje/Documents/GitHub/42_Get_Next_Line/subject.txt", O_RDONLY);
	char *a = get_next_line(fd);
	printf("%s", a);
}
