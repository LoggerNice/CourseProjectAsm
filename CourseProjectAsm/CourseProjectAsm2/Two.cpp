#include <iostream>
#include <windows.h>
#include <string>

//Функция обработки датчика качества видео
void processingQuality(int sens)
{
	_asm
	{
		Quality_:					; Качество видео
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
	printf("Имеется возможность просмотра 4к\n");
	_asm
	{
			jmp exit_

		isMore2_:
	}
	printf("Можете просматривать видео в 2к\n");
	_asm
	{
			jmp exit_

		isMore3_:
	}
	printf("Ваша связь позволяет просмотр в 1080р\n");
	_asm
	{
			jmp exit_

		isMore4_:
	}
	printf("Стандартное качество просмотра видео 720р, но можно сделать лучше\n");
	_asm
	{
			jmp exit_

		isMore5_: 
	}
	printf("Качество видео низкое. Обновите интернет ПО, либо обратитесь к провайдеру!\n");
	_asm
	{
			jmp exit_

		error_:
	}
	printf("Не удалось обнаружить данные! Проверьте вашу связь\n");
	_asm
	{
			jmp exit_

		exit_ :
	}
}

//Функция обработки датчика частоты кадров
void processingFrequency(int sens)
{
	_asm
	{
		Frequency_:					; Частота
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
	printf("Все прекрасно. Видео просматривается в 240 FPS\n");
	_asm
	{
			jmp exit_

		isMore2_:
	}
	printf("Хорошая частота. Видео просматривается в 144 FPS\n");
	_asm
	{
			jmp exit_

		isMore3_:
	}
	printf("Средняя частота. Видео просматривается в 60 FPS\n");
	_asm
	{
			jmp exit_

		isMore4_:
	}
	printf("Обычная частота. Видео просматривается в 30 FPS\n");
	_asm
	{
			jmp exit_

		error_:
	}
	printf("Низкая частота. Обновите комплектующие!\n");
	_asm
	{
			jmp exit_

		exit_:
	}
}

//Функция обработки датчика интернет соединения
void processingInternet(int sens)
{
	_asm
	{
		Connection_:				; Соединение интернета
			cmp sens, 1
			je isMore1_
			cmp sens, 0
			je isMore2_
			jmp error_

		isMore1_:
	}
	printf("Интернет-соединение имеется\n");
	_asm
	{
			jmp exit_

		isMore2_:
	}
	printf("Интернет-соединение отсутствует\n");
	_asm
	{
			jmp exit_

		error_:
	}
	printf("Датчик вышел из строя!\n");
	_asm
	{
			jmp exit_

		exit_:
	}
}

//Функция записи данных
int* sensorDataCollection()
{
	int sens[3];

	_asm
	{
		rdtsc
		mov eax, eax
		mov edx, 60				; Верхняя граница рандома 0
		mov ebx, 244			; Нижняя граница рандома 240
		div ebx
		mov [sens + 4], edx		; Частота
		xor eax, eax
		xor edx, edx
		xor ebx, ebx

		rdtsc
		mov eax, eax
		mov edx, 0				; Верхняя граница рандома 0
		mov ebx, 2				; Нижняя граница рандома 1
		div ebx
		mov [sens + 8], edx		; Интернет
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
			mov edx, 3; Верхняя граница рандома 0
			mov ebx, 35; Нижняя граница рандома 35
			div ebx
			mov sens, edx; Качество
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
		printf("Пожалуйста, подождите. Получаем данные...\n");
		loading();

		sensor = sensorDataCollection();
		int resQuallity = sensor[0];
		int resFrequency = sensor[1];
		int resInternet = sensor[2];

		printf("Датчик качества видео: %i\n", resQuallity);
		Sleep(1000);
		printf("Датчик частоты кадров: %i\n", resFrequency);
		Sleep(1000);
		printf("Датчик интернет соединения: %i\n\n", resInternet);
		Sleep(1000);

		printf("Результат первого датчика: ");
		processingQuality(resQuallity);
		Sleep(1000);
		printf("Результат второго датчика: ");
		processingFrequency(resFrequency);
		Sleep(1000);
		printf("Результат третьего датчика: "); 
		processingInternet(resInternet);

		Sleep(5000);
		printf("\nОбновляем данные...\n");
		loading();
		Sleep(1000);
		system("cls");
	}

	system("pause");
	return 0;
}