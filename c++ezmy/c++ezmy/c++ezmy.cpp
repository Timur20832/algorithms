/*17. ��������� ������� ��������  ������.  �������  �  ������
1-31,243-255 �� ������,  �.�. ��� ����� ������ ���� ���������.
�������� ��������� ��������-���������� ����������  �����. ���� 
�� ������ ���� ������� �� ����������� ������  �������  �������
������ �� ����� ������. �������� � ������������� �����  ������
����� ���������� ������ (8). ������������ ����� ��-23*/
#include <iostream>
#include <fstream>
#include <string>
using namespace std;
const int top_border = 242;
const int bot_border = 32; // ������� � ������� ������� �������
char descript(char ch, int key);
char encode(char ch, int key);

int main() 
{
	setlocale(LC_ALL, "RU");
	string strc;
	char ch;
	int 
		flag = 0, // �������� �� ���������� key
		key = 3, // ������� ������ �� ��������� 3 �� �������
		index; // ��� ������� ��������/����������

	cout << "�������� -> 1; ���������� -> 2" << endl;
	cin >> index;

	cout << "���� ���������� ������" << endl;
	cin >> strc;
	ifstream file_input(strc);

	cout << "���� ���������� ������" << endl;
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
			cout << "�����?";
			return 0;
		}
	}
	else 
	{
		cout << "���� �� ������";
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
