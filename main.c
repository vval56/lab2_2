#include "header.h"

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Использование: %s <имя_файла>\n", argv[0]);
        return 1;
    }

    char *filename = argv[1];
    FILE *file = fopen(filename, "wt");
    if (!file) {
        puts("Ошибка открытия файла");
        return 1;
    }

    char ** text = NULL;
    int rows = 0;

    puts("Введите текст(пустая строка для завершения):");

    inputText(&text, &rows);

    for (int i = 0; i < rows; i++) {
        fprintf(file, "%s\n", text[i]);
    }

    free(text);
}
