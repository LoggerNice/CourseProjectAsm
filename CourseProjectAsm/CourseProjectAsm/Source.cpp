#include <iostream>
#include "time.h"

int main()
{
	setlocale(LC_ALL, "RUS");

	srand(time(NULL));
	const int N = 5;
	int firstArray[N];
	int secondArray[N];
	int thirdArray[N];

	for (int i = 0; i < N; i++) {
		firstArray[i] = 1 + rand() % 10;
		secondArray[i] = 1 + rand() % 10;
	}

	_asm 
	{
		mov	eax, firstArray
		mov	edx, secondArray
		mov	ecx, thirdArray
	}

	printf("Результат: ");

	for (int i = 0; i < N; i++)
		printf("%i ", thirdArray[i]);

	system("pause");
	return 0;
}