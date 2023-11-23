#include "Thx.h"
#include <iostream>

// применение функции активации(вектор значений, размер)
void Thx::use(double* value, int n) {
	for (int i = 0; i < n; i++) {
		if (value[i] < 0)
			value[i] = 0.01 * (exp(value[i]) - exp(-value[i])) / (exp(value[i]) + exp(-value[i]));
		else
			value[i] = (exp(value[i]) - exp(-value[i])) / (exp(value[i]) + exp(-value[i]));
	}
}

// применение производной  функции активации(вектор значений, размер)
void Thx::useDer(double* value, int n) {
	for (int i = 0; i < n; i++) {
		if (value[i] < 0)
			value[i] = 0.01 * (1 - value[i] * value[i]);
		else
			value[i] = 1 - value[i] * value[i];
	}
}

// просто перегруженная функция 
double Thx::useDer(double value) {
	if (value < 0)
		value = 0.01 * (exp(value) - exp(-value)) / (exp(value) + exp(-value));
	else
		value = (exp(value) - exp(-value)) / (exp(value) + exp(-value));
	return value;
}