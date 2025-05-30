
#pragma once
#include <iostream>
#include <vector>
#include <map>
#include <list>
#include <fstream>
#include <string>
void coding();
void decode();
using namespace std;
inline int** degenerate_matrix(int** mtr, int n) {
	int** mtrc = new int* [n];
	int m = 97;
	for (int i = 0; i < n; ++i) {
		mtrc[i] = new int[n];
	}
	if (mtr[0][0] == 0) { mtr[0][0] = 1; }
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			mtrc[i][j] = mtr[i][j];
		}
	}
	int bug = 0;
	int op = mtr[0][0];
	for (int k = 1; k < n; k++) {
		for (int i = k; i < n; i++) {
			int mn1 = mtr[k - 1][k - 1];
			int	mn2 = mtr[i][k - 1];
			for (int j = 0; j < n; j++) {
				mtr[i][j] = (mtr[i][j] * mn1 - mtr[k - 1][j] * mn2) % m;
				if (mtr[i][j] < 0) { mtr[i][j] = mtr[i][j] + m; }
			}

		}
		if (mtr[k][k] == 0) { mtrc[k][k] += 1; mtr[k][k] = op; }
		op *= mtr[k][k] % m;
	}
	if (mtr[n - 1][n - 1] == 0) { mtrc[n - 1][n - 1] += 1; mtr[n - 1][n - 1] = op; }
	return mtrc;
}
inline int uf30(int x) {
	int kb = 8;
	//cout << bitset<8>(x) << endl;
	//int m1 = x >> 7;// � m1 �� ����� �������� ���� - �������� �������� ���� ��������� �����
	int m1 = x >> (kb - 1);
	//cout << bitset<10>(m1) << endl;
	//int m2 = (x & 1) << 9;//� m2 �� ����� ��������  ���� - �������� �������� ���� ��������� �����
	int m2 = (x & 1) << (kb + 1);
	x = x << 1;
	x = x | m1 | m2;// 0 ���-7 ��� ��������� �����, � 1 �� 8- ���� �����, 9 ���-0 ��� �����
	int m = 1;
	int y = 0;
	//for (int i = 8; i > 0; i = i - 1) {//���������� ������ �������� ���
	for (int i = kb; i > 0; i = i - 1) {
		//��������� ��������� �� ������� 000-0 001-1 010-1 011-1 100-1 101-0 110-0 111-0
		//cout << i << endl;
		//cout << bitset<10>(m1) << endl;
		int x1 = x & 7;//�������� ������  ��� � 0 �� 2
		//cout << bitset<10>(x1) << endl;
		x = x >> 1;//�������� ����� ����� �������� ��������� ������
		if (0 < x1 && x1 < 5) { y = y | m; }//
		//y = y >> 1;
		m = m << 1;
	}
	return y;
}
inline void cdelatK1(int* K1) {
	//int K1[256] = { 0 };
	int p = 0;
	//for (int i = 0; i < 256; i++) { cout << i << " - " << uf(i) << endl; }
	for (int i = 0; i < 256; i++) { K1[i] = uf30(i); }
	//for (int i = 0; i < 256; i++) { cout << i << " - " << K1[i] << endl; }
	for (int i = 0; i < 256; i++) {
		//cout << i << "--";
		for (int j = 0; j < 256; j++) {
			p = 0;
			//if (K1[j] == i) { cout << j << " "; }
		}
		//cout << endl;
	//	cout << "    ";
	}
	int m = 0; int n = 0;
	int V[10] = { 0 }; int I[10] = { 0 };
	for (int i = 0; i < 256; i++) {
		n++;
		V[n] = i;
		for (int j = 0; j < 256; j++) {
			if (K1[j] == i) {
				m++;
				I[m] = j;
			}
		}
		while (m != 0 && n != 0) {
			K1[I[m]] = V[n];
			m--; n--;
		}
	}
	//for (int i = 0; i < 256; i++) {
	//	cout << i << " - " << K1[i] << endl;
	//}
}
inline int da(int** mtr, int k) {
	int A = 0, B = 0, C = 0;
	for (int i = 0; i < k; i++) {
		for (int j = 0; j < k; j++) {
			A = mtr[i][j];
			int B = A & 1;
			B = B << 8;
			A = A | B;
			A = A << 1;
			A = A | (A >> 8);
			int M[8] = { 0,1,1,1,1,0,0,0 };
			for (int ix = 0; ix < 8; ix++) {
				int msk = 7;
				int tri = msk & A;
				cout << M[tri];
				C = C | (M[tri] << i);
				A = A >> 1;
			}
			mtr[i][j] = C;
		}
	}
}
inline int** matrix_mult(int** a, int** b, int k) {
	int** c = new int* [k];
	for (int i = 0; i < k; i++) {
		c[i] = new int[k];
		for (int j = 0; j < k; j++) {
			c[i][j] = 0;
		}
	}
	for (int i = 0; i < k; i++) {
		for (int j = 0; j < k; j++) {
			for (int m = 0; m < k; m++) {
				c[i][j] += a[i][m] * b[m][j];
				//*c[i][j] = c[i][j] % 97;
			}
		}
	}
	for (int i = 0; i < k; i++) {
		for (int j = 0; j < k; j++) {
			c[i][j] = c[i][j] % 97;
		}
	}
	return c;
}

inline bool cheak_key(string key) {
	for (int i = 0; i < key.size(); i++) {
		if (key[i] < 32 || key[i]>127) { return false; }
	}
	return true;
}
//****������� ����� a �� ������ b
inline int mod(int a, int b) {
	if (a < 0) return a % b + b;
	return a % b;
}
//**** ���������� ������������ �� ��������� ��������
inline void next_route(int* r, int n) {
	int i = n - 1;//�������� � ����� �������� ������������
	int j = n - 1;
	while (r[i - 1] > r[i]) { //��������� �����, ���� ������� ���������� ��������
		i--;
	}                          //�������� � ����� �������� ������������
	while (r[j] < r[i - 1]) { //���� ������� ������ ��� ��������� 
		j--;
	}
	int x = r[i - 1]; // ������ �� �������
	r[i - 1] = r[j];
	r[j] = x;
	for (int k = i, m = n - 1; k < m; k++, m--) {
		int c = r[k];//����������� "�����"
		r[k] = r[m];
		r[m] = c;
	}
}
//**** ��������� ������������ ������� ������� ������������
//�.�. ��� ����� n! ���������, ������ �� ������� ���� ������������
// n ��������� �������, ������ � ����������� ������
inline int chek_det(int** mtr, int n) {
	int nf = 1;
	int* r = new int[n];
	for (int i = 0; i < n; i++) { r[i] = i; }//��������� ������������
	int P = 1, S = 0, f = 0;
	for (int i = 1; i <= n; i++) {//������� n!(���������� ������������)
		nf = nf * i;
	}
	for (int i = 0; i < nf; i++) {//������ �������� ����� - ��������� ������������
		for (int x = 0; x < n; x++) {//���������� �������� � ������������
			for (int y = x + 1; y < n; y++) {//�.�. ����� ��� � �������
				if (r[x] > r[y]) { f++; };//����� ����� ������ �������
			}
		}
		for (int j = 0; j < n; j++) {//������� ������������ ���������, 
			P = mtr[j][r[j]] * P;//��������������� ������ ������������
		}//����� ������-������� �����, ����� �������-���� �����
		next_route(r, n);// �������� ������������
		if (f % 2 != 0) { P = -P; };// ���������� ���� ������������ 
		//���� ����� �������� - ��������, �� ���� ������ �� ���������������
		S = P + S;
		P = 1;
		f = 0;
	}

	return S;
}
//**** ������� ����������� �������-�����
inline int matrix_size(string str) {
	int N = str.length();
	int k = sqrt(N);// ������� ����� ����� ����� �� ���������� ���������
	if (k * k != N) { k++; }//���� ���������� ��������� �� ����� ��������
	//��  k ���� �� ������� ������
	if (k == 1) { k = 2; }  //���� � ����� ����� ���� ������, ������� ��� 
	return k;               //���� ����� 2 �� 2
}
//**** ������ �������-���� �� ������-�����
inline int** create_mtr(int k, string str) {
	int** mtr = new int* [k];
	int z = 0;
	for (int i = 0; i < k; i++) {
		mtr[i] = new int[k];
		for (int j = 0; j < k; j++) {//��������� ��������� �������
			mtr[i][j] = 35;     // �������� "*" 
		}//����� ������� ���� ���������� ��������
	}//� ����� ������ ��� k � ��������, �� ���������� ����� = 35
	for (int i = 0; i < k; i++) {   //��������� ������� �������,���������������� 
		for (int j = 0; j < k; j++) {//�������� ������-�����
			if (z != str.length()) {
				mtr[i][j] = str[z] - 30;
				z++;
			}
		}
	}
	return mtr;
}
//**** ������ ����� ��� �������� (o-����� ������,p-����� �������)
inline int** minor_seach(int** mtr, long long n, long long o, long long p) {
	int* minor = new int[n * n - 2 * n + 1];  //������ ������ �����������
	int** minor_mtr = new int* [n];      // (n-1) � ��������
	for (int i = 0; i < n; i++) { minor_mtr[i] = new int[n]; }
	int z = 0;
	for (int i = 0; i < n; i++) {  //������� � ������ ���������������
		for (int j = 0; j < n; j++) {  // �������� ������� ����� ���������,� �������
			if (i != o && j != p) { minor[z] = mtr[i][j]; z++; }
		}  // ����� ������=o  ��� ����� �������=p
	}
	z = 0;
	for (int i = 0; i < n - 1; i++) {  //��������� �� ������� ������� �����������
		for (int j = 0; j < n - 1; j++) {  //(n-1) �� (n-1)
			minor_mtr[i][j] = minor[z];
			z++;
		}
	}
	return minor_mtr;
}
//**** ������������� �������
inline int** trans(int** mtr, int n) {
	int** mtr_copy = new int* [n];
	for (int i = 0; i < n; i++) {
		mtr_copy[i] = new int[n];
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			mtr_copy[j][i] = mtr[i][j];
		}
	}

	return mtr_copy;
}
//**** ������ �������� ������� ����������� n �� n �� ������ 97
inline int** invers(int** mtr, int n) {
	int** mtr_inv = new int* [n];
	for (int i = 0; i < n; i++) { mtr_inv[i] = new int[n]; }

	int S = chek_det(mtr, n); // S - ������������ ������� �����
	S = mod(S, 97);
	// ���� �������� ������� x � ������������ S �� ������ 97. 
	// (������ ����������  ����������� �������� �������). ��� ��� S � 97 
	// ������� ������� , ��  x  ����������� ���������� 
	// � �������� ������ ���������  S*x=1 (mod 97). ����� 
	// ������������  ������� ���������  ��������� �������.
	int x = 0, y = 0;
	while (y != 1) {
		x = x + 1;
		y = (S * x) % 97;
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {   //��� ������� �������� �������
			int** min = minor_seach(mtr, n, i, j); // ������  �����
			int det = chek_det(min, n - 1);// ������� ������������ ������
			mtr_inv[i][j] = mod(pow(-1, i + j) * det, 97);// ���������� ���� 
			//���� ������������ �� mod 97
			mtr_inv[i][j] = mod(mtr_inv[i][j] * x, 97); // �������� �� �������� �������
			// ������������, ���� �� mod 97

		}

	}
	mtr_inv = trans(mtr_inv, n);   //������������� �������
	return mtr_inv;
}
