#pragma once
#include <iostream>
#include "Sigmoid.h"
#include "ReLU.h"
#include "Thx.h"
// my

enum activateFunc { sigmoid = 1, reLU, thx };

class ActivateFunctuon:public Sigmoid, public ReLU, public Thx{
	activateFunc actFunc;
public:
	ActivateFunctuon() {
        actFunc = reLU;
	}
	void set();
	void use(double* value, int n);
	void useDer(double* value, int n);
	double useDer(double value);
};

