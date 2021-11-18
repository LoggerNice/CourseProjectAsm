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

	printf("������� �����: ");
	scanf("%i", &inputNum);

	for (int i = 0; i < N; i++) 
	{
		firstArray[i] = 1 + rand() % 10;
		secondArray[i] = 1 + rand() % 10;
	}


	_asm 
	{
		mov ecx, 0								; �������
		mov ebx, inputNum						; ���������������� ����������
		lea esi, thirdArray						; ������ ������
		lea edi, firstArray						; ������ ������
		lea edx, secondArray					; ������ ������
		jmp loopFor_
		
		next_:
			inc ecx
			cmp ecx, N
			jg exit_
			jmp loopFor_

		loopFor_:
			xor eax, eax						; ������������ eax
			add eax, [edi + ecx * 4]			; ����� �������� ������� �������
			add eax, [edx + ecx * 4]			; ����� �������� ������� �������

			cmp eax, ebx						; ��������� �����
			jg isMore_							; ���� ������
			jmp isSmall_						; ���� ������

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


	printf("\n������ ������: ");
	write(firstArray, N);
	printf("������ ������: ");
	write(secondArray, N);
	printf("�������� ������: ");
	write(thirdArray, N);

	printf("����� ������: %i � �����: %i\n\n", countOne, countNull);

	system("pause");
	return 0;
}