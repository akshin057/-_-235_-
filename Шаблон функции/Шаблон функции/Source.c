#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include<string.h>
#define _USE_MATH_DEFINES
#include <math.h>



struct material {
	char name[30];
	double price;
	double squaresInEach;
};

struct land {
	char materialName[30];
	int boxes;
	double price;
	double squaresInBox;
};

int main() {
	setlocale(LC_ALL, "RUS");
	struct material materials[5];
	int count = 0;
	
	char line[100] = "1  Монолитный пенобетон      |      1700        |        5           |";

	int k = 0; 

	for (int i = 0; i < strlen(line); i++)
	{
		
		if (line[2+i] == ' ')
		{
			k++;
			if (k == 3)
			{
				materials[count].name[i] = '\0';
				break;
			}
		}
		materials[count].name[i] = line[2 + i];

	}

	
	printf("Имя материала - %s", materials[count].name);
	 

	return 0;
}

