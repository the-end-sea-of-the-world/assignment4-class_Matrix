#include "Matrix.h"
#include <iostream>
using namespace std;

Matrix::Matrix() {
	rowN = 0;
	colN = 0;
	data = new float* [2];
	data[0] = new float[1];
	data[0][0] = '/0';
	data[1] = new float[2];
	data[1][0] = 1;
	data[1][1] = '/0';
}

Matrix::Matrix(int rN, int cN, float** d) {
	rowN = rN;
	colN = cN;
	if (d) {
		data = new float* [rN + 1];
		for (int i = 0; i < rN; i++) {
			data[i] = d[i];
		}
		data[rN] = new float[2];
		data[rN][0] = 2;
		data[rN][1] = '/0';
	}
	else {
		data = new float* [rN + 1];
		for (int i = 0; i < rN; i++) {
			data[i] = new float[cN];
		}
		data[rN] = new float[2];
		data[rN][0] = 1;
		data[rN][1] = '/0';
	}
}

Matrix::Matrix(const Matrix& a) {
	rowN = a.rowN;
	colN = a.colN;
	data = a.data;
	data[rowN][0]++;
}

Matrix::~Matrix() {
	if (data[rowN][0]>1) {
		data[rowN][0]--;
	}
	else {
		for (int i = 0; i <= rowN;i++) {
			delete[] data[i];
		}
		delete[] data;
	}
}

int Matrix::getRowN()  const {
	return rowN;
}
int Matrix::getColN()  const {
	return colN;
}
float** Matrix::getData()  const {
	return data;
}
void Matrix::setData(int i,int j,float c) {
	if (1 <= i && i <= rowN && 1 <= j && j <= colN) data[i - 1][j - 1] = c;
	else cout << "Coordinate error!" << endl;
}

Matrix& Matrix::operator=(const Matrix& a) {
	if (this==&a) {
		return *this;
	}
	if (this->data[this->rowN][0] > 1) {
		this->data[this->rowN][0]--;
	}
	else {
		for (int i = 0; i <= this->rowN; i++) {
			delete[] this->data[i];
		}
		delete[] this->data;
	}
	this->colN = a.colN;
	this->rowN = a.rowN;
	this->data = a.data;
	this->data[this->rowN][0]++;
	return *this;
}

Matrix Matrix::operator+(const Matrix& a)  const {
	if (rowN!=a.rowN || colN!=a.colN) {
		cout << "These two matrices cannot be added!" << endl;
		return Matrix();
	}
	else {
		Matrix result = Matrix(a.rowN,a.colN);
		for (int i = 0; i < a.rowN;i++) {
			for (int j = 0; j < a.colN;j++) {
				result.data[i][j] = this->data[i][j] + a.data[i][j];
			}
		}
		return result;
	}
}
Matrix Matrix::operator-(const Matrix& a)  const {
	if (rowN != a.rowN || colN != a.colN) {
		cout << "These two matrices cannot be subtracted!" << endl;
		return Matrix();
	}
	else {
		Matrix result = Matrix(a.rowN, a.colN);
		for (int i = 0; i < a.rowN; i++) {
			for (int j = 0; j < a.colN; j++) {
				result.data[i][j] = this->data[i][j] - a.data[i][j];
			}
		}
		return result;
	}
}
ostream& operator<<(ostream& os, const Matrix& a) {
	os << "[";
	for (int i = 0; i < a.rowN; i++) {
		for (int j = 0; j < a.colN; j++) {
			os << " " << a.data[i][j];
		}
		if (i == a.rowN - 1) os << " ]";
		else os << endl;
	}
	return os;
}

Matrix Matrix::operator*(const Matrix& a) const {
	if (this->colN != a.rowN) {
		cout << "These two matrices cannot be multiplied!\n";
		return Matrix();
	}
	else {
		Matrix m = Matrix(this->rowN,a.colN);
		for (int i = 0; i < m.rowN; i++) {
			for (int j = 0; j < m.colN; j++) {
				m.data[i][j] = 0;
				for (int k = 0; k < this->colN; k++) {
					m.data[i][j] += this->data[i][k] * a.data[k][j];
				}
			}
		}
		return m;
	}
}
Matrix Matrix::operator*(double c) const {
	Matrix m = Matrix(this->rowN, this->colN);
	for (int i = 0; i < this->rowN; i++) {
		for (int j = 0; j < this->colN; j++) {
			m.data[i][j] = this->data[i][j] * c;
		}
	}
	return m;
}
Matrix operator*(double c, const Matrix& a) {
	return a * c;
}
