#include "ReLU.h"

// применение функции активации(вектор значений, размер)
void ReLU::use(double* value, int n) {
	for (int i = 0;i < n;i++) {
		if (value[i] < 0)
			value[i] *= 0.01;
		else if (value[i] > 1)
			value[i] = 1. + 0.01 * (value[i] - 1.);
	}
}

// применение производной  функции активации(вектор значений, размер)
void ReLU::useDer(double* value, int n) {
	for (int i = 0; i < n; i++) {
		if (value[i] < 0 || value[i] > 1)
			value[i] = 0.01;
		else
			value[i] = 1;
	}
}

// просто перегруженная функция 
double ReLU::useDer(double value) {
	if (value < 0 || value > 1)
		value = 0.01;
	return value;
}
