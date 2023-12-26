#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include<string.h>
#define _USE_MATH_DEFINES
#include <math.h>
#define MAX_MATERIALS 100  // ������������ ���������� ����������


//��������� �������
struct location input();//���� ������
double calculate(double x, double y);//������� �������
struct material* readMaterialsFromFile(const char* fname, int* materialCount);//���������� �������� ���������� � ������ �������� 
int calculatingTheBoxes(struct location land);//������� ���������� ������� ��� �������� �������
double coveringPart(struct location land);//���� �������� �������, ������� �������� ��������
double priceCalculation(struct location land);//������� ���� ��������
void printingTheLand(struct location land);//����� ������� 

// ��������� ��� �������� ���������� � ������ ����������
struct material {
	char name[30];
	double price;
	double squareMeters;
};

// ��������� ��� �������� ���������� �� ������� � ��������� ��������� ��������
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
	printf("                              ����������� ������� ������������������ ��������� ��� ������-���������� �������\n");
	struct location land;
	
	char fname[20] = "Materials.txt"; //��� �����

	while (1)
	{
		land = input();//���� ������

		land.square = calculate(land.width, land.length);//������� �������
		printf("������� ������� ����� %.1lf ���������� ������\n", land.square);
		printf("���������� ����������?(�� - ����� �����, ��� - 0)\n");
		int k;
		scanf("%d", &k);
		if (k == 0)
		{
			return 1;
		}

		while (1) {
			printf("                                                   ������� ����\n");
			printf("�������� c�������� ���� ���������� ���������\n");
			printf("1-����� ���������\n");
			printf("2-������� ���������� ������� ��� ��������\n");
			printf("3-������� ���� �������� �������\n");
			printf("4-����� �������� �������\n");
			int c;
			scanf("%d", &c);

			switch (c)
			{
			case 1:
				// ����� �������
				printf("�������� �������� �� ������\n");
				int materialCount; //���������� ����� ���������
				struct material* materials = readMaterialsFromFile(fname, &materialCount);//������ �������� ����������
				int g;
				for (int i = 0; i < materialCount; i++) {
					printf("%d. ��������: %s;\n����: %.2lf; ���������� ��. ������ � ��������: %.2lf;\n\n",
						i + 1, materials[i].name, materials[i].price, materials[i].squareMeters);
				}
				scanf("%d", &g);//����� ���������

				strcpy(land.materialName, materials[g - 1].name);
				printf("�� ������� �������� - %s\n", land.materialName);
				land.materialPrice = materials[g - 1].price;
				land.squareMeters = materials[g - 1].squareMeters;
				break;

			case 2:
				land.coveredSquare = coveringPart(land);
				land.boxes = calculatingTheBoxes(land);

				if (land.boxes % 10 > 0 && land.boxes % 10 < 5)
				{
					printf("��� �������� ��������� ������� ������� ����������� %d �������� ���������\n", land.boxes);
				}
				else
				{
					printf("��� �������� ��������� ������� ����������� %d �������� ���������\n", land.boxes);
				}
				break;
			    
			case 3:
				land.coveredSquare = coveringPart(land);
				land.priceOfCovering = priceCalculation(land);
				printf("��� �������� ��������� ������� ��������� ���������� ����������� %.1lf ������\n", land.priceOfCovering);
				break;
			case 4:
				land.coveredSquare = coveringPart(land);
				printingTheLand(land);
				break;
			default:
				printf("������ ������ ��� � ������\n�������� ������\n");
				continue;
			}
			printf("���������� ���������� ���������?(�� - ����� �����; ��� - 0)\n");
			int p;
			scanf("%d", &p);
			if (p == 0)
			{
				break;
			}
		}
		printf("��������� ��������� ������?(�� - ����� �����; ��� - 0)\n");
		scanf("%d", &k);
		if (k == 0)
		{
			return 1;
		}

	}
    system("pause");
}


struct location input() { //���� ������ � ����������: ������� ����������� ��������� �������� ��������� ���������
	printf("������� ����� ������� � ������:\n");
	struct location land;
	scanf("%lf", &land.length);

	while (land.length < 0)//���� �������� ������������, ������������ ������ ��������� ���� ������
	{
		printf("������� ������������� ��������. ���������� ���������� �����\n");
		scanf("%lf", &land.length);
	}

	printf("������� ������ ������� � ������:\n");
	scanf("%lf", &land.width);
	while (land.width < 0)//���� �������� ������������, ������������ ������ ��������� ���� ������
	{
		printf("������� ������������� ��������. ���������� ���������� �����\n");
		scanf("%lf", &land.width);
	}

	return land;
}

double calculate(double x, double y) {
	double square = x * y;
	return square;
}

struct material* readMaterialsFromFile(char* fname, int* materialCount) {
	FILE* file = fopen(fname, "r");//�������� ����� 
	if (!file) {
		puts("�� ������� ������� ����");
		return 0;
	}

	struct material* materials = malloc(MAX_MATERIALS * sizeof(struct material));//�������� ������� ��������
	if (!materials) {
		puts("�� ������� �������� ������ ��� ������� ��������");
		return 0;
	}

	int count = 0;
	char line[500];

	
	while (fgets(line, sizeof(line), file) != NULL && count < MAX_MATERIALS) { //���������� ������ �� �����

		if (line[0] == ' ' || line[0] == '�')//������� ������ ���� ����� �������
		{
			continue;
		}
		
		for (int i = 0; i < strlen(line); i++)//������������ � �������� ��������� �������� �� �����
		{

			if (line[2 + i] == ' ' && line[2 + 1 + i] == ' ')//��������� ������������
			{
				materials[count].name[i] = '\0';
				break;
			}
			materials[count].name[i] = line[2 + i];
		}




		char buffer[1000];

		for (int i = 0; i < strlen(line); i++)
		{
			buffer[i] = line[30 + i];//��������� ������
		}

		sscanf(buffer, " %lf |   %lf ", &materials[count].price, &materials[count].squareMeters);//������������ � ���� � ���-�� ��������� ��������� �� �����

		count++;
	}

	fclose(file);
	
	
	*materialCount = count; //������� ���-�� ����� ���������

	return materials;
}

double coveringPart(struct location land) {
	printf("������� (� ���������) ����� �������, ������� �� ������ ������� ��������� ����������\n����� ������� ���� ������� ������� 1\n");
	scanf("%d", &land.part);
	while (land.part > 100 || land.part < 0)
	{
		printf("������� �� ����� ���� ���������.\n���������� ��� ���\n");
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
	if (land.materialName[0] == '�' && land.materialName[1] == '�') {
		printf("�� ��������� ������ �������� ''���������� ���������'' ���������� 1700 ������ �� 5 ���������� ������ � ��������\n");
		land.squareMeters = 5;
	}

	land.boxes = ceil((land.coveredSquare) / land.squareMeters);

	return land.boxes;
}

double priceCalculation(struct location land) {
	if (land.materialName[0] == '�' && land.materialName[1] == '�') {
		printf("�� ��������� ������ �������� ''���������� ���������'' ���������� 1700 ������ �� 5 ���������� ������ � ��������\n");
		land.squareMeters = 5;
		land.materialPrice = 1700;
	}

	land.boxes = ceil((land.coveredSquare) / land.squareMeters);
	
	land.priceOfCovering = land.boxes * land.materialPrice;

	return land.priceOfCovering;
}

void printingTheLand(struct location land) {
	printf("����� �������� �������\n");
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


