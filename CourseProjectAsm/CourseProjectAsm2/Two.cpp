#include <iostream>
#include <windows.h>
#include <string>

//������� ��������� ������
int* processing(int sensor[])
{
	int res[3];

	_asm
	{
		Quality_:					; �������� �����
			cmp sens, 35
			jg isMore1_
			cmp sens, 24
			jg isMore2_
			cmp sens, 8
			jg isMore3_
			cmp sens, 3
			jg isMore4_
		
		Frequency_:					; �������. �������� ��� �����
			cmp [sens + 4], 35
			jg isMore1_
			cmp [sens + 4], 24
			jg isMore2_
			cmp [sens + 4], 8
			jg isMore3_
			cmp [sens + 4], 3
			jg isMore4_


		isMore1_:
			mov res, 1
			jmp Frequency_

		isMore2_:
			mov res, 2
			jmp Frequency_

		isMore3_:
			mov res, 3
			jmp Frequency_

		isMore4_:
			mov res, 4
			jmp Frequency_
	}

	return res;
}

//������� ������ ������
int* sensorDataCollection()
{
	int sens[3];

	_asm
	{
		rdtsc
		mov eax, eax
		mov edx, 3				; ������� ������� ������� 0
		mov ebx, 35				; ������ ������� ������� 35
		div ebx
		mov sens, edx			; ��������
		xor eax, eax
		xor edx, edx
		xor ebx, ebx

		rdtsc
		mov eax, eax
		mov edx, 60				; ������� ������� ������� 0
		mov ebx, 240			; ������ ������� ������� 240
		div ebx
		mov [sens + 4], edx		; �������
		xor eax, eax
		xor edx, edx
		xor ebx, ebx

		rdtsc
		mov eax, eax
		mov edx, 0				; ������� ������� ������� 0
		mov ebx, 2				; ������ ������� ������� 1
		div ebx
		mov [sens + 8], edx		; ��������
		xor eax, eax
		xor edx, edx
		xor ebx, ebx
	}

	return sens;
}

void loading()
{
	printf("[");
	for (int i = 0; i < 30; i++) {
		Sleep(100);
		printf(":");
	}
	printf("]\n\n");
}

int main()
{
	setlocale(LC_ALL, "RUS");

	int* sensor;

	while (true)
	{
		system("color 0e");
		printf("����������, ���������. �������� ������\n");
		loading();

		sensor = sensorDataCollection();

		printf("������ �������� �����: %i \n������ ������� ������: %i\n������ �������� ����������: %i\n\n", sensor[0], sensor[1], sensor[2]);
		processing(sensor);

		Sleep(50000);
		printf("��������� ������\n");
		loading();
		Sleep(1000);
		system("cls");
	}

	system("pause");
	return 0;
}