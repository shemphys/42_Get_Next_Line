#include <stdlib.h>
#include <unistd.h>

#ifndef BUFFER_SIZE
#define BUFFER_SIZE 42
#endif

typedef struct s_fragment {
    char *data;
    size_t len;
    struct s_fragment *next;
} t_fragment;

t_fragment *fragment_create(char *data, size_t len) {
    t_fragment *frag = malloc(sizeof(t_fragment));
    if (!frag) return NULL;
    frag->data = data;
    frag->len = len;
    frag->next = NULL;
    return frag;
}

char *get_next_line(int fd) {
    static char buffer[BUFFER_SIZE + 1];
    char *line = NULL;
    ssize_t read_bytes;
    size_t i, j, buffer_len = 0;
    t_fragment *head = NULL, *tail = NULL, *frag;
    size_t line_len = 0;

    while (1) {
        // Keep reading until buffer is full or a newline is found
        while (buffer_len < BUFFER_SIZE && buffer[buffer_len] != '\n') {
            read_bytes = read(fd, buffer + buffer_len, BUFFER_SIZE - buffer_len);
            if (read_bytes < 0) {
                free(line);
                return NULL; // Reading error
            }
            buffer_len += read_bytes;

            if (read_bytes == 0)
                break; // End of file
        }

        buffer[buffer_len] = '\0'; // Ensure the buffer is a valid string

        // Find a newline in the buffer
        for (i = 0; i < buffer_len && buffer[i] != '\n'; i++);

        // If a newline was found or end of file reached...
        if (i < buffer_len && buffer[i] == '\n' || read_bytes == 0) {
            // Create a new fragment with the buffer's content
            frag = fragment_create(buffer, i);
            if (!frag) return NULL; // Memory error

            // Add the fragment to the list
            if (!head) head = frag;
            if (tail) tail->next = frag;
            tail = frag;
            line_len += frag->len;

            // If a newline was found...
            if (i < buffer_len && buffer[i] == '\n') {
                // Combine all fragments into the final line
                line = malloc((line_len + 1) * sizeof(char));
                if (!line) return NULL; // Memory error

                char *ptr = line;
                while (head) {
                    frag = head;
                    for (j = 0; j < frag->len; j++)
                        *(ptr++) = frag->data[j];
                    head = frag->next;
                    free(frag);
                }
                *ptr = '\0';

                // Shift remaining buffer content to the beginning
                for (j = 0; buffer[i] != '\0'; j++, i++)
                    buffer[j] = buffer[i];
                buffer_len -= i;

                return line;
            }

            // Shift remaining buffer content to the beginning
            for (j = 0; buffer[i] != '\0'; j++, i++)
                buffer[j] = buffer[i];
            buffer_len -= i;
        }

        if (read_bytes == 0)
            return NULL; // End of file
    }
}
