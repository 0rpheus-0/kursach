#include "ActivateFunctuon.h"

//// применение функции активации(вектор значений, размер)
//void ActivateFunctuon::use(double* value, int n) {
//	for (int i = 0;i < n;i++)
//		value[i] = 1 / (1 + exp(-value[i]));
//}
//
//// применение производной  функции активации(вектор значений, размер)
//void ActivateFunctuon::useDer(double* value, int n) {
//	for (int i = 0;i < n;i++)
//		value[i] *=  (1 + -value[i]);
//}
//
//// просто перегруженная функция 
//double ActivateFunctuon::useDer(double value) {
//	return value = 1 / (1 + exp(-value));
//}

void ActivateFunctuon::set() {
	std::cout << "Set actFunc pls\n1 - Sigmoid \n2 - ReLU \n3 - Th(x) \n";
	int tmp;
	std::cin >> tmp;
	switch (tmp)
	{
	case sigmoid:
		actFunc = sigmoid;
		break;
	case reLU:
		actFunc = reLU;
		break;
	case thx:
		actFunc = thx;
		break;
	default:
		throw std::runtime_error("Error read actFunc");
		break;
	}
}

// применение функции активации(вектор значений, размер)
void ActivateFunctuon::use(double* value, int n) {
	switch (actFunc)
	{
	case sigmoid:
		Sigmoid::use(value, n);
		break;
	case reLU:
		ReLU::use(value, n);
		break;
	case thx:
		Thx::use(value, n);
		break;
	default:
		throw std::runtime_error("Error actFunc \n");
		break;
	}
}

// применение производной  функции активации(вектор значений, размер)
void ActivateFunctuon::useDer(double* value, int n) {
	switch (actFunc)
	{
		switch (actFunc)
		{
		case sigmoid:
			Sigmoid::useDer(value, n);
			break;
		case reLU:
			ReLU::useDer(value, n);
			break;
		case thx:
			Thx::useDer(value, n);
			break;
		default:
			throw std::runtime_error("Error actFunc \n");
			break;
		}
	default:
		throw std::runtime_error("Error actFuncDer \n");
		break;
	}
}

// просто перегруженная функция 
double ActivateFunctuon::useDer(double value) {
	switch (actFunc)
	{
		switch (actFunc)
		{
		case sigmoid:
			Sigmoid::useDer(value);
			break;
		case reLU:
			ReLU::useDer(value);
			break;
		case thx:
			Thx::useDer(value);
			break;
		default:
			throw std::runtime_error("Error actFunc \n");
			break;
		}
	}
	return value;
}