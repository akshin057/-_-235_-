#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include<string.h>
#define _USE_MATH_DEFINES
#include <math.h>
#define MAX_MATERIALS 100  // Максимальное количество материалов


//Прототипы функций
struct location input();//ввод данных
double calculate(double x, double y);//подсчет площади
struct material* readMaterialsFromFile(const char* fname, int* materialCount);//присвоение каталога материалов в массив структур 
int calculatingTheBoxes(struct location land);//подсчет количества коробок для покрытия участка
double coveringPart(struct location land);//ввод процента участка, который подлежит покрытию
double priceCalculation(struct location land);//подсчет цены покрытия
void printingTheLand(struct location land);//схема участка 

// Структура для хранения информации о списке материалов
struct material {
	char name[30];
	double price;
	double squareMeters;
};

// Структура для хранения информации об участке и выбранном материале покрытия
struct location {
	double width;
	double length;
	double square;
	int part;
	double coveredSquare;
	char materialName[30];
	double materialPrice;
	double squareMeters;
	double priceOfCovering;
	int boxes;
 };

int main() {
	setlocale(LC_ALL, "RUS");
	printf("                              Калькулятор расчета теплоизоляционного материала для садово-огородного участка\n");
	struct location land;
	
	char fname[20] = "Materials.txt"; //имя файла

	while (1)
	{
		land = input();//ввод данных

		land.square = calculate(land.width, land.length);//площадь участка
		printf("Площадь участка равна %.1lf квадратных метров\n", land.square);
		printf("Продолжить вычисления?(Да - любое число, нет - 0)\n");
		int k;
		scanf("%d", &k);
		if (k == 0)
		{
			return 1;
		}

		while (1) {
			printf("                                                   Главное меню\n");
			printf("Выберите cледующий этап выполнения программы\n");
			printf("1-Выбор материала\n");
			printf("2-Подсчет количества коробок для покрытия\n");
			printf("3-Подсчет цены покрытия участка\n");
			printf("4-Схема покрытия участка\n");
			int c;
			scanf("%d", &c);

			switch (c)
			{
			case 1:
				// вызов функции
				printf("Выберите материал из списка\n");
				int materialCount; //количество видов материала
				struct material* materials = readMaterialsFromFile(fname, &materialCount);//массив структур материалов
				int g;
				for (int i = 0; i < materialCount; i++) {
					printf("%d. Название: %s;\nЦена: %.2lf; Количество кв. метров в упаковке: %.2lf;\n\n",
						i + 1, materials[i].name, materials[i].price, materials[i].squareMeters);
				}
				scanf("%d", &g);//выбор материала

				strcpy(land.materialName, materials[g - 1].name);
				printf("Вы выбрали материал - %s\n", land.materialName);
				land.materialPrice = materials[g - 1].price;
				land.squareMeters = materials[g - 1].squareMeters;
				break;

			case 2:
				land.coveredSquare = coveringPart(land);
				land.boxes = calculatingTheBoxes(land);

				if (land.boxes % 10 > 0 && land.boxes % 10 < 5)
				{
					printf("Для покрытия выбранной площади участка потребуется %d упаковки материала\n", land.boxes);
				}
				else
				{
					printf("Для покрытия выбранной площади потребуется %d упаковок материала\n", land.boxes);
				}
				break;
			    
			case 3:
				land.coveredSquare = coveringPart(land);
				land.priceOfCovering = priceCalculation(land);
				printf("Для покрытия выбранной площади выбранным материалом потребуется %.1lf рублей\n", land.priceOfCovering);
				break;
			case 4:
				land.coveredSquare = coveringPart(land);
				printingTheLand(land);
				break;
			default:
				printf("Такого пункта нет в списке\nВыберите другой\n");
				continue;
			}
			printf("Продолжить выполнение программы?(Да - любое число; Нет - 0)\n");
			int p;
			scanf("%d", &p);
			if (p == 0)
			{
				break;
			}
		}
		printf("Запустить программу заново?(Да - любое число; Нет - 0)\n");
		scanf("%d", &k);
		if (k == 0)
		{
			return 1;
		}

	}
    system("pause");
}


struct location input() { //ввод данных с клавиатуры: функция присваивает введенные значения атрибутам структуры
	printf("Введите длину участка в метрах:\n");
	struct location land;
	scanf("%lf", &land.length);

	while (land.length < 0)//если значение отрицательно, пользователя просят повторить ввод данных
	{
		printf("Введено отрицательное значение. Пожалуйста попробуйте снова\n");
		scanf("%lf", &land.length);
	}

	printf("Введите ширину участка в метрах:\n");
	scanf("%lf", &land.width);
	while (land.width < 0)//если значение отрицательно, пользователя просят повторить ввод данных
	{
		printf("Введено отрицательное значение. Пожалуйста попробуйте снова\n");
		scanf("%lf", &land.width);
	}

	return land;
}

double calculate(double x, double y) {
	double square = x * y;
	return square;
}

struct material* readMaterialsFromFile(char* fname, int* materialCount) {
	FILE* file = fopen(fname, "r");//открытие файла 
	if (!file) {
		puts("Не удалось открыть файл");
		return 0;
	}

	struct material* materials = malloc(MAX_MATERIALS * sizeof(struct material));//Создание массива структур
	if (!materials) {
		puts("Не удалось выделить память для массива структур");
		return 0;
	}

	int count = 0;
	char line[500];

	
	while (fgets(line, sizeof(line), file) != NULL && count < MAX_MATERIALS) { //считывание строки из файла

		if (line[0] == ' ' || line[0] == '№')//пропуск первых двух строк таблицы
		{
			continue;
		}
		
		for (int i = 0; i < strlen(line); i++)//присваивание в название материала название из файла
		{

			if (line[2 + i] == ' ' && line[2 + 1 + i] == ' ')//остановка присваивания
			{
				materials[count].name[i] = '\0';
				break;
			}
			materials[count].name[i] = line[2 + i];
		}




		char buffer[1000];

		for (int i = 0; i < strlen(line); i++)
		{
			buffer[i] = line[30 + i];//обрезание строки
		}

		sscanf(buffer, " %lf |   %lf ", &materials[count].price, &materials[count].squareMeters);//присваивание в цену и кол-во квадратов материала из файла

		count++;
	}

	fclose(file);
	
	
	*materialCount = count; //подсчет кол-ва видов материала

	return materials;
}

double coveringPart(struct location land) {
	printf("Введите (в процентах) часть участка, которую вы хотите покрыть выбранным материалом\nЧтобы покрыть весь участок введите 1\n");
	scanf("%d", &land.part);
	while (land.part > 100 || land.part < 0)
	{
		printf("Условие не может быть выполнено.\nПопобруйте еще раз\n");
		scanf("%d", &land.part);
	}
	if (land.part == 1)
	{
		land.coveredSquare = land.square;
	}
	else
	{ 
		land.coveredSquare = land.square * ((double)land.part / 100);
	}
	
	return land.coveredSquare;
}

int calculatingTheBoxes(struct location land) {
	if (land.materialName[0] == 'М' && land.materialName[1] == 'М') {
		printf("По умолчанию выбран материал ''Монолитный пенобетон'' стоимостью 1700 рублей за 5 квадратных метров в упаковке\n");
		land.squareMeters = 5;
	}

	land.boxes = ceil((land.coveredSquare) / land.squareMeters);

	return land.boxes;
}

double priceCalculation(struct location land) {
	if (land.materialName[0] == 'М' && land.materialName[1] == 'М') {
		printf("По умолчанию выбран материал ''Монолитный пенобетон'' стоимостью 1700 рублей за 5 квадратных метров в упаковке\n");
		land.squareMeters = 5;
		land.materialPrice = 1700;
	}

	land.boxes = ceil((land.coveredSquare) / land.squareMeters);
	
	land.priceOfCovering = land.boxes * land.materialPrice;

	return land.priceOfCovering;
}

void printingTheLand(struct location land) {
	printf("Схема покрытия участка\n");
	int k = ceil(land.coveredSquare / land.width);
	for (int i = 1; i <= land.length; i++)
	{
		for (int j = 1; j <= land.width; j++)
		{
			if (i == 1 || i == land.length)
			{
				printf("* ");
				continue;
			}
			if (i <= k)
			{
				printf("* ");
			}
			else if (j == 1 || j == land.width)
			{
				printf("* ");
			}
			else
			{
				printf("  ");
			}
			}
		printf("\n");	
	}
}


