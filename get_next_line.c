#include <stdlib.h>
#include <unistd.h>

#ifndef BUFFER_SIZE
#define BUFFER_SIZE 42
#endif

char *str_append(char *line, char *buffer, size_t len) {
	size_t i = 0;
	size_t line_len = 0;
	size_t j = 0;

	if (line) {
		while (line[line_len])
			line_len++;
	}
	char *new_line = malloc((line_len + len + 1) * sizeof(char));
	if (!new_line) return NULL;
	while (line && line[i]) {
		new_line[i] = line[i];
		i++;
	}
	while (j < len) {
		new_line[i + j] = buffer[j];
		j++;
	}
	new_line[i + j] = '\0';
	free(line);
	return new_line;
}

char *get_next_line(int fd) {
	static char buffer[BUFFER_SIZE + 1];
	char *line = NULL;
	ssize_t read_bytes;
	size_t i;
	size_t j;

	while ((read_bytes = read(fd, buffer, BUFFER_SIZE)) >= 0) {
		buffer[read_bytes] = '\0';

		for (i = 0; i < read_bytes && buffer[i] != '\n'; i++);

		line = str_append(line, buffer, i);
		if (!line) return NULL;

		if (i < read_bytes && buffer[i] == '\n') {
			for (j = i + 1; j <= read_bytes; j++)
				buffer[j - i - 1] = buffer[j];
			return line;
		}
		if (read_bytes < BUFFER_SIZE) return line;
	}
	free(line);
	return NULL;
}
