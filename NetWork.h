#pragma once
#include <iostream>
#include <fstream> 
#include "Matrix.h"
#include "ActivateFunctuon.h"
#include "Sigmoid.h"
#include "ReLU.h"
#include "Thx.h"

// информация о сети
struct data_NetWork {
    int L;      // количество слоев
    int* size;  // количество слоёв на каждом слое
};


class NetWork {
	int L; // колличество слоёв 
	int* size; // количество нейронов на каждом слое 
	ActivateFunctuon actFunc; // функция активации  
	Matrix* weight; // матрица весов
	double** bios; // веса смещений 
	double** neuros_val, ** neuros_err; //значение нейронов, ошибки для нейронов
	double* neuros_bios_val; // значение нейронов смешения 
public:
    void Init(data_NetWork data);
    //void Init();
    void ReadDataNetWork(std::string path);
	void PrintConfig();
	void SetInput(double* values);

	double ForwarFeed();
	int SearchMaxIndex(double* values);
	void PrintValue(int L);

	void BackPropogation(double expert);
	void WeightsUpdater(double lr);

	void SaveWeights();
	void ReadWeights();
};

