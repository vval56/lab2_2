#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void checkSpace(char *line) {
    int spaceCount = 0;
    for (int i = 0; line[i] != '\0'; i++) {
        if (line[i] == ' ') {
            spaceCount++;
            if (spaceCount > 1) {
                puts("Слишком много пробелов. Введите еще раз.");
                return;
            }
        } else {
            spaceCount = 0;
        }
    }
}

void inputText(char ***text, int *rows) {
    size_t n = 0;
    char *line = NULL;
    ssize_t read;

    *rows = 0;

    while (1) {

        read = getline(&line, &n, stdin);

        if (read == -1) {
            puts("Ошибка чтения строки.");
            free(line);
            exit(1);
        }

        if (line[read - 1] == '\n') {
            line[read - 1] = '\0';
            read--;
        }

        if (read == 0) {
            break;
        }

        checkSpace(line);

        *text = (char **)realloc(*text, sizeof(char *) * (*rows + 1));
        if (*text == NULL) {
            puts("Ошибка перераспределения памяти.");
            free(line);
            exit(1);
        }

        (*text)[*rows] = (char *)malloc((read + 1) * sizeof(char));
        if ((*text)[*rows] == NULL) {
            puts("Ошибка выделения памяти для строки.");
            free(line);
            for (int i = 0; i < *rows; i++) {
                free((*text)[i]);
            }
            free(*text);
            exit(1);
        }

        strcpy((*text)[*rows], line);
        (*rows)++;
    }

    free(line);
}
