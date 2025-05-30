#include <iostream>  
#include <vector>
#include <map>
#include <list>
#include <fstream>
#include <string>
#include "Header.h"
//Для текста и ключа можно использовать символы, аски-код которых лежит
//в пределах промежутка [32,127]. Каждому символу ставится в соответствие
//число равное аски-код минус 30. Переходу на следущую строку (подряд 
//стоящие аски-коды 10 и 13) соответствует число 0. Число 1 указывает окончание текста. 
using namespace std;
void main() {
	setlocale(LC_ALL, "Russian");
	//string key = "abcd";
	//string text = "exp(A+2)*C=?";
	int* K1{ new int[256] };
	cdelatK1(K1);
	ifstream file1;
	ofstream file_cip;
	string key_tr;
	int key_str[100] = { 0 };
	//int key_mtr[10][10] = { 0 };
	int file_str[100] = { 0 };
	int p = 5;// размерность строки-ключа
	int n = 4;//размерность матрицы ключа
	int k = 0;
	int m = 97;//количество символов в алфавите
	char buff;
	bool fl = true;
	file1.open("12.txt", ios::in | ios::binary);
	file_cip.open("112.txt", ios::in | ios::trunc);
	if (!file1.is_open()) { cout << "Файл не открыт" << endl; return; }
	else if (file1.peek() == EOF) { cout << "Файл пуст" << endl; return; }
	else { cout << "Файл успешно открыт" << endl; }
	int** key_mtr = new int* [n];
	for (int i = 0; i < n; ++i) {
		key_mtr[i] = new int[n];
	}

	while (true) {
		cout << "Введите ключ" << endl;
		cin >> key_tr;
		if (!cheak_key(key_tr)) { cout << "недопустимый ключ" << endl; }
		else { break; }
	}
	for (int i = 0; i < key_tr.size(); i++) { key_str[i] = key_tr[i]; }
	while (fl) {
		for (int i = 0; i < n; i++) {//формируем блок символов
			buff = file1.get(); // считываем очередной символ
			//cout << (char)buff << " ";
			if (buff > 126 || (buff < 32 && buff != 13 && buff != 10 && buff != -1)) {//проверка на допустимость
				cout << "Файл содержит недопустимые символы" << endl;
				file1.close(); file_cip.close(); return;
			}
			if (buff == 13) { buff = file1.get(); buff = 30; }//если в ключе есть перенос строки
			if (file1.eof()) {// если текст  закончился
				fl = false; n = i;
			}
			//cout << (char)buff << " ";
			file_str[i] = buff - 30;// если текст не закончился
			//cout << (char)buff << " ";
		}

		//for (int i = 0; i < n; i++) { cout << (char)file_str[i] << " "; } cout << endl<<endl;
		//cout << endl << endl;

		for (int i = 0; i < n; i++) {//формируем матрицу ключ размерности n
			for (int j = 0; j < n; j++) {
				key_str[k] = K1[key_str[k]];
				key_mtr[i][j] = key_str[k];
				k++;
				if (k == p) { k = 0; };
			}
		}

		int x = key_mtr[n - 1][n - 1];
		int y = 1;
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				y = key_mtr[i][j];
				if (x == 0) { x = 1; }
				if (y == 0) { y = 1; }
				//if (key_mtr[i][j] == 0) { key_mtr[i][j] = 1; }
				key_mtr[i][j] = (max(x, y) % min(x, y)) % m;
				x = y;
				//key_mtr[i][j] = key_mtr[i][j] % m;
			}
		}
		//for (int i = 0; i < n; i++) {
			//for (int j = 0; j < n; j++) {
			//	cout << key_mtr[i][j] << " ";
			//}
		//	cout << endl;
		//}
		if (n != 0) {
			key_mtr = degenerate_matrix(key_mtr, n);//проверяем на вырожденность
		}
		for (int i = 0; i < n; i++) { // кодируем i-элемент полученного вектора
			int S = 0;
			for (int j = 0; j < n; j++) {
				S = S + key_mtr[i][j] * file_str[j];
			}
			S = (S % 97) + 30; // получаем аски - код  шифрованного символа
			cout << (char)S << " "; // выводим этот символ на экран
			file_cip.write((char*)&S, sizeof(char)); //записываем его  в  файл

		}

		
		//for (int i = 0; i < n; i++) { cout << file_str[i] << " "; }cout << endl<<endl;
	}
	cout << endl;
	file1.close();
	file_cip.close();
	decode();
}
