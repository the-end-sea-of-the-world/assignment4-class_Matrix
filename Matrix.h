#pragma once
#include <iostream>
using namespace std;

class Matrix
{
private:
	int rowN;
	int colN;
	float** data;

public:
	Matrix();
	Matrix(int rN,int cN,float** d=0);
	Matrix(const Matrix& a);

	~Matrix();

	int getRowN() const;
	int getColN() const;
	float** getData() const;
	void setData(int i, int j, float c);

	Matrix& operator=(const Matrix& a);
	Matrix operator+(const Matrix& a) const;
	Matrix operator-(const Matrix& a) const;
	Matrix operator*(const Matrix& a) const;
	Matrix operator*(double c) const;

	friend Matrix operator*(double c, const Matrix& a);
	friend ostream& operator<<(ostream& os, const Matrix& a);
};
