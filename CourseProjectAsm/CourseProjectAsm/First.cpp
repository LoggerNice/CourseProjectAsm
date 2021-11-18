#include <iostream>
#include "time.h"

void write(int *array, const int count) 
{
	for (int i = 0; i < count; i++)
	{
		printf("%i ", array[i]);
	}
	printf("\n");
}

int main()
{
	setlocale(LC_ALL, "RUS");

	srand(time(NULL));
	const int N = 5;
	int firstArray[N];
	int secondArray[N];
	int thirdArray[N] = {0};
	int inputNum;
	int dump = 0;
	int countOne = 0;
	int countNull = 0;

	printf("Введите число: ");
	scanf("%i", &inputNum);

	for (int i = 0; i < N; i++) 
	{
		firstArray[i] = 1 + rand() % 10;
		secondArray[i] = 1 + rand() % 10;
	}


	_asm 
	{
		mov ecx, 0								; Счётчик
		mov ebx, inputNum						; Пользовательская переменная
		lea esi, thirdArray						; Третий массив
		lea edi, firstArray						; Первый массив
		lea edx, secondArray					; Второй массив
		jmp loopFor_
		
		next_:
			inc ecx
			cmp ecx, N
			jg exit_
			jmp loopFor_

		loopFor_:
			xor eax, eax						; Освобождение eax
			add eax, [edi + ecx * 4]			; Сумма элемента первого массива
			add eax, [edx + ecx * 4]			; Сумма элемента первого массива

			cmp eax, ebx						; Сравнение чисел
			jg isMore_							; Если больше
			jmp isSmall_						; Если меньше

		isMore_:
			mov [esi + ecx * 4], 1
			add countOne, 1
			jmp next_

		isSmall_:
			mov [esi + ecx * 4], 0
			jmp next_
		

		exit_:
			xor eax, eax
			mov eax, N
			sub eax, countOne
			mov countNull, eax
	}


	printf("\nПервый массив: ");
	write(firstArray, N);
	printf("Второй массив: ");
	write(secondArray, N);
	printf("Итоговый массив: ");
	write(thirdArray, N);

	printf("Всего единиц: %i и нулей: %i\n\n", countOne, countNull);

	system("pause");
	return 0;
}