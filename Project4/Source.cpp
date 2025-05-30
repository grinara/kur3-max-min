#include <iostream>  
#include <vector>
#include <map>
#include <list>
#include <fstream>
#include <string>
#include "Header.h"
//��� ������ � ����� ����� ������������ �������, ����-��� ������� �����
//� �������� ���������� [32,127]. ������� ������� �������� � ������������
//����� ������ ����-��� ����� 30. �������� �� �������� ������ (������ 
//������� ����-���� 10 � 13) ������������� ����� 0. ����� 1 ��������� ��������� ������. 
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
	int p = 5;// ����������� ������-�����
	int n = 4;//����������� ������� �����
	int k = 0;
	int m = 97;//���������� �������� � ��������
	char buff;
	bool fl = true;
	file1.open("12.txt", ios::in | ios::binary);
	file_cip.open("112.txt", ios::in | ios::trunc);
	if (!file1.is_open()) { cout << "���� �� ������" << endl; return; }
	else if (file1.peek() == EOF) { cout << "���� ����" << endl; return; }
	else { cout << "���� ������� ������" << endl; }
	int** key_mtr = new int* [n];
	for (int i = 0; i < n; ++i) {
		key_mtr[i] = new int[n];
	}

	while (true) {
		cout << "������� ����" << endl;
		cin >> key_tr;
		if (!cheak_key(key_tr)) { cout << "������������ ����" << endl; }
		else { break; }
	}
	for (int i = 0; i < key_tr.size(); i++) { key_str[i] = key_tr[i]; }
	while (fl) {
		for (int i = 0; i < n; i++) {//��������� ���� ��������
			buff = file1.get(); // ��������� ��������� ������
			//cout << (char)buff << " ";
			if (buff > 126 || (buff < 32 && buff != 13 && buff != 10 && buff != -1)) {//�������� �� ������������
				cout << "���� �������� ������������ �������" << endl;
				file1.close(); file_cip.close(); return;
			}
			if (buff == 13) { buff = file1.get(); buff = 30; }//���� � ����� ���� ������� ������
			if (file1.eof()) {// ���� �����  ����������
				fl = false; n = i;
			}
			//cout << (char)buff << " ";
			file_str[i] = buff - 30;// ���� ����� �� ����������
			//cout << (char)buff << " ";
		}

		//for (int i = 0; i < n; i++) { cout << (char)file_str[i] << " "; } cout << endl<<endl;
		//cout << endl << endl;

		for (int i = 0; i < n; i++) {//��������� ������� ���� ����������� n
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
			key_mtr = degenerate_matrix(key_mtr, n);//��������� �� �������������
		}
		for (int i = 0; i < n; i++) { // �������� i-������� ����������� �������
			int S = 0;
			for (int j = 0; j < n; j++) {
				S = S + key_mtr[i][j] * file_str[j];
			}
			S = (S % 97) + 30; // �������� ���� - ���  ������������ �������
			cout << (char)S << " "; // ������� ���� ������ �� �����
			file_cip.write((char*)&S, sizeof(char)); //���������� ���  �  ����

		}

		
		//for (int i = 0; i < n; i++) { cout << file_str[i] << " "; }cout << endl<<endl;
	}
	cout << endl;
	file1.close();
	file_cip.close();
	decode();
}
