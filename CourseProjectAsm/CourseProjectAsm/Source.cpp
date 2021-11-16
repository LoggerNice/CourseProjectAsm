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
	int thirdArray[N];
	int inputNum;
	int dump;
	unsigned short countNull = 0;
	unsigned short countOne = 0;

	printf("������� �����: ");
	scanf("%i", &inputNum);

	for (int i = 0; i < N; i++) 
	{
		firstArray[i] = 1 + rand() % 10;
		secondArray[i] = 1 + rand() % 10;
	}

	//eax, ebx, edx, ecx, al, ah

	_asm 
	{
		mov ax, 0								; ��������
		mov bx, 0								; ������� �����
		mov ebx, inputNum						; ���������������� ����������
		lea eax, firstArray						; ������ ������
		lea edx, secondArray					; ������ ������

		loopFor_:
			xor ecx, ecx						; ���������� ��� ����� �����
			add ecx, eax
			add ecx, edx

			cmp ecx, ebx						; ��������� �����
			jge isMore_							; ���� ������
			jmp isSmall_						; ���� ������

		isSmall_:
			lea ecx, thirdArray
			mov ecx, 1
			jmp next_

		isMore_:
			lea ecx, thirdArray
			mov ecx, 0
			inc bx
			jmp next_
		
		next_:
			cmp ax, 5
			je exit_

			inc ax
			jne loopFor_

		exit_:
			mov thirdArray, ecx
			mov countNull, bx
			mov ax, 5							; ��� ������������� ��������
			sub ax, bx							; ���������
			mov countOne, ax
	}
	 

	/*for (int i = 0; i < N; i++) 
	{
		dump = firstArray[i] + secondArray[i];
		if (dump > inputNum) 
		{
			thirdArray[i] = 1;
		}
		else 
		{
			thirdArray[i] = 0;
			countNull++;
		}
	}*/


	printf("\n������ ������: ");
	write(firstArray, N);
	printf("������ ������: ");
	write(secondArray, N);
	printf("�������� ������: ");
	write(thirdArray, N);

	printf("����� �����: %i � ������: %i\n\n", countNull, 5 - countNull);

	system("pause");
	return 0;
}