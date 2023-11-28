/*17. Придумать систему шифрации  текста.  Символы  с  кодами
1-31,243-255 не менять,  т.к. они могут играть роль служебных.
Написать программу шифрации-дешифрации текстового  файла. Шифр 
не должен быть основан на однозначной замене  каждого  символа
другим по всему тексту. Исходный и зашифрованный файлы  должны
иметь одинаковый размер (8). Сахабутдинов Тимур ПС-23*/
#include <iostream>
#include <fstream>
#include <string>
using namespace std;
const int top_border = 242;
const int bot_border = 32; // границы в которых шифруем символы
char descript(char ch, int key);
char encode(char ch, int key);

int main() 
{
	setlocale(LC_ALL, "RU");
	string strc;
	char ch;
	int 
		flag = 0, // отвечает за увелечение key
		key = 3, // шифрует символ на следующий 3 от данного
		index; // для запроса шифрации/дешифрации

	cout << "Шифрация -> 1; Дешифрация -> 2" << endl;
	cin >> index;

	cout << "Файл считывания текста" << endl;
	cin >> strc;
	ifstream file_input(strc);

	cout << "Файл вписывания текста" << endl;
	cin >> strc;
	ofstream file_output(strc);

	if (file_input) 
	{
		if (index == 1) 
		{
			while (file_input.get(ch)) 
			{
				if (uint8_t(ch) >= 32 && uint8_t(ch) <= 242) 
				{
					file_output << encode(ch, key);
					flag++;
					if (flag == 50) 
					{
						key++;
						flag = 0;
						if (key == 30) 
						{
							key = 3;
						}
					}
				}
				else 
				{
					file_output << ch;
				}
			}
		}
		else if (index == 2) 
		{
			while (file_input.get(ch)) 
			{
				if (uint8_t(ch) >= 32 && uint8_t(ch) <= 242) 
				{
					file_output << descript(ch, key);
					flag++;
					if (flag == 50) 
					{
						key++;
						flag = 0;
						if (key == 30) 
						{
							key = 3;
						}
					}
				}
				else 
				{
					file_output << ch;
				}
			}
		}
		else 
		{
			cout << "дурак?";
			return 0;
		}
	}
	else 
	{
		cout << "Файл не найден";
	}

	file_output.close();
	file_input.close();
	return 0;
}

char descript(char ch, int key) {
	if (uint8_t(ch) - key < bot_border) {
		return char(top_border + uint8_t(ch) + 1 - bot_border - key);
	}
	else {
		return char(uint8_t(ch) - key);
	}
}

char encode(char ch, int key) {
	if (uint8_t(ch) + key > top_border) {
		return char((uint8_t(ch) + key) - top_border + bot_border - 1);
	}
	else {
		return char(uint8_t(ch) + key);
	}
}
