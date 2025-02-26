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

        if (read == 1 && line[0] == '\n') {
            break;
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

        strcpy((*text)[(*rows)++], line);
    }

    free(line);
}

int coutWordsInFile(char * filename){
    FILE * file = fopen(filename, "rt");
    int words = 0, i = 1;
    char buff;

    while(fread(&buff, sizeof(char), 1, file) == 1){
        fseek(file, i * sizeof(char), SEEK_SET);

        if(buff == ' ' || buff == '\0' || buff == '\n'){
            fseek(file, (i++) * sizeof(char), SEEK_SET);
            words++;
        }

        i++;
    }

    fclose(file);

    return words;
}

void findLongestInFile(char *filename, int *position, int *size) {
    FILE *file = fopen(filename, "rt");
    if (!file) {
        puts("Ошибка открытия файла");
        exit(1);
    }

    int currentSize = 0, startPos = 0, currentPos = 0;
    char buff;

    *position = 0;
    *size = 0;

    while ((buff = fgetc(file)) != EOF) {
        if (buff == ' ' || buff == '\n' || buff == '\t') {
            if (currentSize > *size) {
                *position = startPos;
                *size = currentSize;
            }
            currentSize = 0;
            startPos = currentPos + 1;
        } else {
            currentSize++;
        }
        currentPos++;
    }

    if (currentSize > *size) {
        *position = startPos;
        *size = currentSize;
    }

    fclose(file);
}

void swapInFile(char *filename, int *position, int *size) {
    FILE *file = fopen(filename, "r+");
    if (!file) {
        puts("Ошибка открытия файла");
        exit(1);
    }

    char *buffer = (char *)malloc((*size) * sizeof(char));
    if (!buffer) {
        puts("Ошибка выделения памяти");
        fclose(file);
        exit(0);
    }

    fseek(file, *position, SEEK_SET);
    fread(buffer, sizeof(char), *size, file);

    for (int i = 0; i < *size / 2; i++) {
        char temp = buffer[i];
        buffer[i] = buffer[*size - i - 1];
        buffer[*size - i - 1] = temp;
    }

    fseek(file, *position, SEEK_SET);
    fwrite(buffer, sizeof(char), *size, file);

    free(buffer);
    fclose(file);
}

void reverseLongestInFile(char *filename) {
    int position, size;
    findLongestInFile(filename, &position, &size);
    swapInFile(filename, &position, &size);
}

void printFile(char *filename) {
    FILE *file = fopen(filename, "rt");
    if (!file) {
        puts("Ошибка при открытии файла.");
        exit(0);
    }

    char buffer[1024];
    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        printf("%s", buffer);
    }

    fclose(file);
}
