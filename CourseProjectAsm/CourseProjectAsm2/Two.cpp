#include <iostream>
#include <windows.h>
#include <string>

//������� ��������� ������� �������� �����
void processingQuality(int sens)
{
	_asm
	{
		Quality_:					; �������� �����
			cmp sens, 35
			jg isMore1_
			cmp sens, 24
			jg isMore2_
			cmp sens, 16
			jg isMore3_
			cmp sens, 8
			jg isMore4_
			cmp sens, 3
			jg isMore5_
			jmp error_

		isMore1_:
	}
	printf("������� ����������� ��������� 4�\n");
	_asm
	{
			jmp exit_

		isMore2_:
	}
	printf("������ ������������� ����� � 2�\n");
	_asm
	{
			jmp exit_

		isMore3_:
	}
	printf("���� ����� ��������� �������� � 1080�\n");
	_asm
	{
			jmp exit_

		isMore4_:
	}
	printf("����������� �������� ��������� ����� 720�, �� ����� ������� �����\n");
	_asm
	{
			jmp exit_

		isMore5_: 
	}
	printf("�������� ����� ������. �������� �������� ��, ���� ���������� � ����������!\n");
	_asm
	{
			jmp exit_

		error_:
	}
	printf("�� ������� ���������� ������! ��������� ���� �����\n");
	_asm
	{
			jmp exit_

		exit_ :
	}
}

//������� ��������� ������� ������� ������
void processingFrequency(int sens)
{
	_asm
	{
		Frequency_:					; �������
			cmp sens, 240
			jg isMore1_
			cmp sens, 144
			jg isMore2_
			cmp sens, 60
			jg isMore3_
			cmp sens, 30
			jg isMore4_
			jmp error_

		isMore1_:
	}
	printf("��� ���������. ����� ��������������� � 240 FPS\n");
	_asm
	{
			jmp exit_

		isMore2_:
	}
	printf("������� �������. ����� ��������������� � 144 FPS\n");
	_asm
	{
			jmp exit_

		isMore3_:
	}
	printf("������� �������. ����� ��������������� � 60 FPS\n");
	_asm
	{
			jmp exit_

		isMore4_:
	}
	printf("������� �������. ����� ��������������� � 30 FPS\n");
	_asm
	{
			jmp exit_

		error_:
	}
	printf("������ �������. �������� �������������!\n");
	_asm
	{
			jmp exit_

		exit_:
	}
}

//������� ��������� ������� �������� ����������
void processingInternet(int sens)
{
	_asm
	{
		Connection_:				; ���������� ���������
			cmp sens, 1
			je isMore1_
			cmp sens, 0
			je isMore2_
			jmp error_

		isMore1_:
	}
	printf("��������-���������� �������\n");
	_asm
	{
			jmp exit_

		isMore2_:
	}
	printf("��������-���������� �����������\n");
	_asm
	{
			jmp exit_

		error_:
	}
	printf("������ ����� �� �����!\n");
	_asm
	{
			jmp exit_

		exit_:
	}
}

//������� ������ ������
int* sensorDataCollection()
{
	int sens[3];

	_asm
	{
		rdtsc
		mov eax, eax
		mov edx, 60				; ������� ������� ������� 0
		mov ebx, 244			; ������ ������� ������� 240
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
		cmp [sens + 8], 1
		je randThird_
		mov sens, 0
		xor eax, eax
		xor edx, edx
		xor ebx, ebx
		jmp exit_

		randThird_:
			rdtsc
			mov eax, eax
			mov edx, 3; ������� ������� ������� 0
			mov ebx, 35; ������ ������� ������� 35
			div ebx
			mov sens, edx; ��������
			xor eax, eax
			xor edx, edx
			xor ebx, ebx

		exit_:
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
		printf("����������, ���������. �������� ������...\n");
		loading();

		sensor = sensorDataCollection();
		int resQuallity = sensor[0];
		int resFrequency = sensor[1];
		int resInternet = sensor[2];

		printf("������ �������� �����: %i\n", resQuallity);
		Sleep(1000);
		printf("������ ������� ������: %i\n", resFrequency);
		Sleep(1000);
		printf("������ �������� ����������: %i\n\n", resInternet);
		Sleep(1000);

		printf("��������� ������� �������: ");
		processingQuality(resQuallity);
		Sleep(1000);
		printf("��������� ������� �������: ");
		processingFrequency(resFrequency);
		Sleep(1000);
		printf("��������� �������� �������: "); 
		processingInternet(resInternet);

		Sleep(5000);
		printf("\n��������� ������...\n");
		loading();
		Sleep(1000);
		system("cls");
	}

	system("pause");
	return 0;
}