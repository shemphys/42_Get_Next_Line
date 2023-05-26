#include <stdlib.h>
#include <unistd.h>

#ifndef BUFFER_SIZE
#define BUFFER_SIZE 42
#endif

char *get_next_line(int fd)
{
    static char *buffer;
    char *line;
    ssize_t read_bytes;
    size_t i, j;

    if (!buffer) {
        buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
        if (!buffer) return NULL; // Fallo de memoria
    }

    while (1) {
        read_bytes = read(fd, buffer, BUFFER_SIZE);
        if (read_bytes < 0) return NULL; // Error de lectura

        buffer[read_bytes] = '\0'; // Asegurarse de que el buffer es una cadena válida

        // Buscar una línea en el buffer
        for (i = 0; buffer[i] != '\n' && buffer[i] != '\0'; i++);

        // Si se ha encontrado una línea...
        if (buffer[i] == '\n' || (i > 0 && buffer[i] == '\0' && read_bytes == 0)) {
            line = malloc((i + 2) * sizeof(char)); // Reservar espacio para la línea y '\n' y '\0'
            if (!line) return NULL; // Fallo de memoria

            for (j = 0; j < i; j++)
                line[j] = buffer[j];

            line[j++] = '\n'; // Añadir '\n' al final de la línea
            line[j] = '\0'; // Terminar la cadena

            // Desplazar el contenido restante del buffer al inicio
            for (j = 0; buffer[i] != '\0'; j++, i++)
                buffer[j] = buffer[i];
            buffer[j] = '\0';

            return line;
        }
        
        if (read_bytes == 0) return NULL; // Final del archivo
    }
}
