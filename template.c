#include <string.h>
#include <stdio.h>
#include <stdlib.h>

struct line {
    int len;      // количество элементов в строке
    int* data;    // указатель на массив целых чисел
};

struct jagged_array {
    int lines_number;      // количество строк
    struct line* data;     // массив структур line
};

// Функция освобождения памяти для jagged_array (полезна при ошибках)
void free_jagged_array(struct jagged_array* arr) {
    if (arr->data) {
        for (int i = 0; i < arr->lines_number; ++i) {
            free(arr->data[i].data);
        }
        free(arr->data);
        arr->data = NULL;
    }
    arr->lines_number = 0;
}

int input(struct jagged_array* arr_ptr, const char* name) {
    FILE* f = fopen(name, "r");
    if (!f) {
        return -1;  // не удалось открыть файл
    }

    char buffer[256];
    int lines_count = 0;

    // ПЕРВЫЙ ПРОХОД: подсчёт строк и количества чисел в каждой строке
    while (fgets(buffer, sizeof(buffer), f)) {
        lines_count++;
    }

    // Выделяем память под массив структур line
    arr_ptr->lines_number = lines_count;
    arr_ptr->data = malloc(lines_count * sizeof(struct line));
    if (!arr_ptr->data) {
        fclose(f);
        return -2;  // ошибка выделения памяти
    }

    // Инициализируем поля len = 0, data = NULL на случай ошибки
    for (int i = 0; i < lines_count; ++i) {
        arr_ptr->data[i].len = 0;
        arr_ptr->data[i].data = NULL;
    }

    // ВТОРОЙ ПРОХОД: теперь читаем числа и заполняем структуры
    rewind(f);

    int current_line = 0;
    while (fgets(buffer, sizeof(buffer), f)) {
        // Сначала подсчитаем, сколько чисел в строке
        int num_count = 0;
        int temp;
        char* p = buffer;
        int offset;
        while (sscanf(p, "%d%n", &temp, &offset) == 1) {
            num_count++;
            p += offset;
        }

        // Выделяем память под данные этой строки
        arr_ptr->data[current_line].len = num_count;
        if (num_count > 0) {
            arr_ptr->data[current_line].data = malloc(num_count * sizeof(int));
            if (!arr_ptr->data[current_line].data) {
                // Ошибка выделения – освобождаем уже выделенное и выходим
                free_jagged_array(arr_ptr);
                fclose(f);
                return -3;
            }

            // Заполняем массив числами
            p = buffer;
            for (int j = 0; j < num_count; ++j) {
                sscanf(p, "%d%n", &arr_ptr->data[current_line].data[j], &offset);
                p += offset;
            }
        } else {
            arr_ptr->data[current_line].data = NULL; // строка пустая
        }

        current_line++;
    }

    fclose(f);
    return 0;  // успех
}