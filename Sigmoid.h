#pragma once
#include <cmath>


class Sigmoid
{
public:
	void use(double* value, int n);
	void useDer(double* value, int n);
	double useDer(double value);
};

