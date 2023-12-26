#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include<string.h>
#define _USE_MATH_DEFINES
#include <math.h>
#define MAX_MATERIALS 100  // Максимальное количество материалов

// Структура для хранения информации о материале
struct Material {
    char name[30];
    double price;
    double squareMeters;
};

// Функция для считывания данных из файла и создания массива структур
struct Material* readMaterialsFromFile(const char* filePath, int* materialCount) {
    FILE* file = fopen(filePath, "r");
    if (!file) {
        perror("Не удалось открыть файл");
        exit(EXIT_FAILURE);
    }

    // Массив структур
    struct Material* materials = malloc(MAX_MATERIALS * sizeof(struct Material));
    if (!materials) {
        perror("Не удалось выделить память для массива структур");
        exit(EXIT_FAILURE);
    }

    int count = 0;
    char line[1000];

    // Считываем строки из файла
    while (fgets(line, sizeof(line), file) != NULL && count < MAX_MATERIALS) {
        
        if (line[0] == ' ' || line[0] == '№')
        {
            continue;
        }
        
        for (int i = 0; i < strlen(line); i++)
        {

            if (line[2 + i] == '|')
            {
                materials[count].name[i] = '\0';
                break;

            }
            materials[count].name[i] = line[2 + i];
        }

        
        
        
        char buffer[1000];

        for (int i = 0; i < strlen(line); i++)
        {
            buffer[i] = line[30 + i];
        }

        sscanf(buffer, " %lf |   %lf ", &materials[count].price, &materials[count].squareMeters);
       
        count++;
    }

    fclose(file);

    // Устанавливаем количество считанных материалов
    *materialCount = count;

    return materials;
}

int main() {
    setlocale(LC_ALL, "RUS");
    const char* filePath = "Materials.txt";  // Укажите фактический путь к вашему файлу
    int materialCount;
    
    // Вызываем функцию для считывания данных из файла
    struct Material* materials = readMaterialsFromFile(filePath, &materialCount);

    for (int i = 0; i < materialCount; i++)
    {
        printf("Название - %s\nЦена за упаковку - %lf\nКол-во квадратов в одной упаковке %lf\n", materials[i].name, materials[i].price, materials[i].squareMeters);

    }
    // Выводим информацию о считанных материалах
    

    // Освобождаем выделенную память для массива структур
    free(materials);

    return 0;
}
