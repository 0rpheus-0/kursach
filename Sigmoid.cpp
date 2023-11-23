#include "Sigmoid.h"
#include <iostream>

// ���������� ������� ���������(������ ��������, ������)
void Sigmoid::use(double* value, int n) {
	for (int i = 0;i < n;i++)
		value[i] = 1 / (1 + exp(-value[i]));
}

// ���������� �����������  ������� ���������(������ ��������, ������)
void Sigmoid::useDer(double* value, int n) {
	for (int i = 0;i < n;i++)
		value[i] *= (1 + -value[i]);
}

// ������ ������������� ������� 
double Sigmoid::useDer(double value) {
	return value = 1 / (1 + exp(-value));
}