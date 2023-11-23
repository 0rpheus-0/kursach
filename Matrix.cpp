#include "Matrix.h"
#include <ctime>
#include <cstdlib>

// инициализация матрицы(строки, столбцы)
void Matrix::Init(int row, int col) {
	this->row = row;
	this->col = col;
	matrix = new double* [row];
	for (int i = 0; i < row; i++)
		matrix[i] = new double[col];

	for (int i = 0; i < row; i++)
		for (int j = 0; j < col; j++)
			matrix[i][j] = 0;
}

// заполнение случайными числами 
void Matrix::Rand() {
	srand(static_cast<unsigned int>(time(0)));
	for (int i = 0; i < row; i++)
		for (int j = 0; j < col; j++)
			matrix[i][j] = ((rand() % 100)) * 0.03 / (row + 35);
}

// умножение на вектор-столбец(матрица, вектор-столбец, размер вектор столбца, результат??)
void Matrix::Multi(const Matrix& m1, const double* neuron, int n, double* c) {
	if (m1.col != n)
		throw std::runtime_error("Error Multi\n");

	for (int i = 0; i < m1.row; i++) {
		double temp = 0;
		for (int j = 0; j < m1.col; j++)
			temp += m1.matrix[i][j] * neuron[j];
		c[i] = temp;
	}
}

// умножение на транспонированную матрицу(матрица, вектор-столбец, размер вектор столбца, результат??)
void Matrix::Multi_T(const Matrix& m1, const double* neuron, int n, double* c) {
	if (m1.row != n)
		throw std::runtime_error("Error Multi\n");

	for (int i = 0; i < m1.col; i++) {
		double temp = 0;
		for (int j = 0; j < m1.row; j++)
			temp += m1.matrix[j][i] * neuron[j];
		c[i] = temp;
	}
}

// сложение векторов(вектор(+результат), вектор, размер)
 void Matrix::SumVector(double* a, const double* b, int n){
	for (int i = 0; i < n; i++)
		a[i] += b[i];
}

 // возращает элемент матрицы
double& Matrix::operator()(int i, int j) {
	return matrix[i][j];
}

std::ostream& operator << (std::ostream& os, const Matrix& m) {
	for (int i = 0; i < m.row; i++)
		for (int j = 0; j < m.col; j++)
			os << m.matrix[i][j] << " ";
	return os;
}

std::istream& operator >> (std::istream& is, Matrix& m) {
	for (int i = 0; i < m.row; i++)
		for (int j = 0; j < m.col; j++)
			is >> m.matrix[i][j];
	return is;
}
