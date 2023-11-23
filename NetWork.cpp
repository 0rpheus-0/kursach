#include "NetWork.h"
#include <fstream> 
#include <ctime>
#include <cstdlib>

// инициализация сети(иформация из файла)
void NetWork::Init(data_NetWork data) {
//void NetWork::Init() {
    std::cout<<"NW"<<std::endl;
	srand(time(NULL));
	srand(static_cast<unsigned int>(time(0)));
    L = data.L;
    /*
    L = 3;
	size = new int[L]; 
    size[0]=784;
    size[1] =256;
    size[2]=10;
    */
    size = new int[L];
	for (int i = 0; i < L;i++)
		size[i] = data.size[i]; // считываем из структуры
    std::cout<<"NW 2"<<std::endl;
	weight = new Matrix[L - 1]; // место для матрицы весов 
	bios = new double* [L - 1]; // для весов смешения 
	for (int i = 0; i < L - 1; i++) {
		weight[i].Init(size[i + 1], size[i]);
		bios[i] = new double[size[i + 1]];
		weight[i].Rand(); // веса заполнили случайно 
		for (int j = 0; j < size[i + 1];j++)
			bios[i][j] = ((rand() % 50) * 0.06 / (size[i] + 15)); // веса смещения заполнили случайно 
	}
	neuros_val = new double* [L]; // место для нейронов  
	neuros_err = new double* [L]; //
	for (int i = 0; i < L; i++) {
		neuros_val[i] = new double[size[i]];
		neuros_err[i] = new double[size[i]];
        for(int j =0; j < size[i]; j++){
            neuros_val[i][j]=0;
            neuros_err[i][j]=0;
        }
	}


	neuros_bios_val = new double[L];
	for (int i = 0; i < L - 1; i++)
		neuros_bios_val[i] = 1;
}

void NetWork::ReadDataNetWork(std::string path) {
    //data_NetWork data{};

    std::ifstream fin;
    fin.open(path);
    if (!fin.is_open()) {
        std::cout << "Error reading the file " << path << std::endl;
        system("pause");
    }
    else
        std::cout << path << " loading...\n";
    std::string temp;
    int n;
    while (!fin.eof()) {
        fin >> temp;
        if (temp == "NetWork") {
            fin >> n;
            L = n;
            //size = new int[L];
            for (int i = 0; i < L; i++) {
                fin >> size[i];
            }
        }
    }


    fin.close();
}

// вывод информации о сети
void NetWork::PrintConfig() {
	std::cout << "_______________________________________\n";
	std::cout << "Network has " << L << " layers\nSIZE[]: ";
	for (int i = 0; i < L; i++)
		std::cout << size[i] << " ";
	std::cout << "\n_______________________________________\n\n";
}

// подаются данные для нейронов(вектора значений)
void NetWork::SetInput(double* values) {
    std::cout<<"SetInp"<<std::endl;
	for (int i = 0; i < size[0]; i++)
		neuros_val[0][i] = values[i];
    std::cout<<"SetInp2"<<std::endl;
}


// функция прямого распространения 
double NetWork::ForwarFeed() {
	for (int i = 1; i < L; i++) {
		Matrix::Multi(weight[i - 1], neuros_val[i - 1], size[i - 1], neuros_val[i]); // матрицу весов на вектор столбец нейронов(матрица весов, значение нейронов, количество нейронов, желаемый результат)
		Matrix::SumVector(neuros_val[i], bios[i - 1], size[i]); // суммируем значение с весами смещения 
		actFunc.use(neuros_val[i], size[i]); // используем функцию активации для нейронов
	}
	return SearchMaxIndex(neuros_val[L - 1]); // ищеи MAX
	//int pred = SearchMaxIndex(neuros_val[L - 1]); // ищеи MAX
	//return pred;
}

// возращает индекс МАХ из вектора значений(вектор значений)
int NetWork::SearchMaxIndex(double* value) {
	double max = value[0];
	int prediction = 0;
	double temp;
	for (int i = 1; i < size[L - 1]; i++) {
		temp = value[i];
		if (temp > max) {
			prediction = i;
			max = temp;
		}
	}
	return prediction;
}

// выводит индекс и значение нейрона на экран на слое (слой)
void NetWork::PrintValue(int L) {
	for (int i = 0; i < size[L]; i++)
		std::cout << i << neuros_val[L][i] << std::endl;
}

// считаем дельту(правильный ответ)
void NetWork::BackPropogation(double expert) {
	for (int i = 0; i < size[L - 1]; i++) {
		if (i != int(expert))
			neuros_err[L - 1][i] = -neuros_val[L - 1][i] * actFunc.useDer(neuros_val[L - 1][i]);
		else
			neuros_err[L - 1][i] = (1.0 - neuros_val[L - 1][i]) * actFunc.useDer(neuros_val[L - 1][i]);
	}
	for (int i = L - 2; i > 0; i--) {
		Matrix::Multi_T(weight[i], neuros_err[i + 1], size[i + 1], neuros_err[i]);
		for (int j = 0; j < size[i]; j++)
			neuros_err[i][j] *= actFunc.useDer(neuros_val[i][j]);
	}
}

// обновление весов
void NetWork::WeightsUpdater(double lr) {
	for (int i = 0; i < L - 1; i++)
		for (int j = 0; j < size[i + 1]; j++)
			for (int k = 0; k < size[i]; k++)
				weight[i](j, k) += neuros_val[i][k] * neuros_err[i + 1][j] * lr; // должен быть +
	for (int i = 0; i < L - 1; i++)
		for (int j = 0; j < size[i + 1]; j++)
			bios[i][j] += neuros_err[i + 1][j] * lr;
}

// сохраняем веса 
void NetWork::SaveWeights() {
	std::ofstream fout;
	fout.open("Weight.txt");
	if (!fout.is_open()) {
		std::cout << "Error reading the file";
		system("pause");
	}

	for (int i = 0; i < L - 1; i++)
		fout << weight[i] << " ";

	for (int i = 0; i < L - 1; i++)
		for (int j = 0; j < size[i + 1]; j++)
			fout << bios[i][j] << " ";

	std::cout << "Weghts saved\n";
	fout.close();
}

// считываем веса
void NetWork::ReadWeights() {
    std::cout<<"weghts1"<<std::endl;
	std::ifstream fin;
    fin.open("D:/Proga/Qt/Weight.txt");
	if (!fin.is_open()) {
        std::cout<<"weghtsNot"<<std::endl;
		std::cout << "Error reading the file";
		system("pause");
	}
    std::cout<<"weghtsYes"<<std::endl;
	for (int i = 0; i < L - 1; i++)
		fin >> weight[i];

	for (int i = 0; i < L - 1; i++)
		for (int j = 0; j < size[i + 1]; j++)
			fin >> bios[i][j];

	std::cout << "Weghts readed\n";
	fin.close();
}
