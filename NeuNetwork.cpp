#include <chrono>
//#include <fstream> 
//#include <string>
#include "NetWork.h"


struct data_info {
    double* pixels;
    int digit;
};

// считывае инфу про сеть (путь)
data_NetWork ReadDataNetWork(std::string path) {
    data_NetWork data{};
    std::ifstream fin;
    fin.open(path);
    if (!fin.is_open()) {
        std::cout << "Error reading the file " << path << std::endl;
        system("pause");
    }
    else
        std::cout << path << " loading...\n";
    std::string temp;
    int L;
    while (!fin.eof()) {
        fin >> temp;
        if (temp == "NetWork") {
            fin >> L;
            data.L = L;
            data.size = new int[L];
            for (int i = 0; i < L; i++) {
                fin >> data.size[i];
            }
        }
    }
    fin.close();
    return data;
}

// считываем инфу для обучения (путь, инфа о сети, колличество примеров)
data_info* ReadData(std::string path, const data_NetWork& data_NW, int& examples) {
    data_info* data;
    std::ifstream fin;
    fin.open(path);
    if (!fin.is_open()) {
        std::cout << "Error reading the file " << path << std::endl;
        system("pause");
    }
    else
        std::cout << path << " loading...\n";

    std::string temp;
    fin >> temp;
    if (temp == "Examples") {
        fin >> examples;
        std::cout << "Examples: " << examples << std::endl;
        data = new data_info[examples];
        for (int i = 0; i < examples; i++)
            data[i].pixels = new double[data_NW.size[0]];

        for (int i = 0; i < examples; i++) {
            fin >> data[i].digit;
            for (int j = 0; j < data_NW.size[0]; j++) 
                fin >> data[i].pixels[j];
        }
        fin.close();
        //NewBase
        std::cout << "NewBase... \n";
        //std::cout << "lib_MNIST loaded... \n";
        return data;
    }
    else {
        std::cout << "Error loading: " << path << std::endl;
        fin.close();
        return nullptr;
    }
}

int main() {
    NetWork NW{};
    data_NetWork NW_config;
    data_info* data;
    ActivateFunctuon Fun;
    double right_answer = 0, right, predict, max_right_answer = 0;
    //double Lr = 0; // попробую
    int epoch = 0;
    bool study, weights, repeat = true;
    std::chrono::duration<double> time;

    NW_config = ReadDataNetWork("Config.txt");
    NW.Init(NW_config);
    NW.PrintConfig();
    Fun.set();

    while (repeat) {

        std::cout << "Study? (1/0)" << std::endl;
        std::cin >> study;
        if (study) {
            
            epoch = 0;
            std::cout << "Read Weights? (1/0)" << std::endl;
            std::cin >> weights;
            if (weights)
                NW.ReadWeights();
            int examples;
            data = ReadData("NewBase.txt", NW_config, examples);
            //data = ReadData("lib_MNIST_edit.txt", NW_config, examples);
            auto begin = std::chrono::steady_clock::now();
            while (right_answer / examples * 100 < 98) {
                right_answer = 0;
                auto t1 = std::chrono::steady_clock::now();
                for (int i = 0; i < examples; i++) {
                    NW.SetInput(data[i].pixels);
                    right = data[i].digit;
                    predict = NW.ForwarFeed();
                    if (predict != right) {
                        NW.BackPropogation(right);
                        NW.WeightsUpdater(0.1);
                        //NW.WeightsUpdater(0.15 * exp(-epoch /*/ 10.*/));// было /20 и 0ю15
                    }
                    else
                        right_answer++;
                }
                auto t2 = std::chrono::steady_clock::now();
                time = t2 - t1;
                if (right_answer > max_right_answer) max_right_answer = right_answer;
                std::cout << "right answer: " << right_answer / examples * 100 << "\t" << "max right answer: " << max_right_answer / examples * 100 << "\t" << "epoch: " << epoch << "\tTIME: " << time.count() << std::endl;
                epoch++;
                //Lr = examples / right_answer  * 10
                if (epoch == 20) // было 20
                    break;
            }
            auto end = std::chrono::steady_clock::now();
            time = end - begin;
            std::cout << "TIME: " << time.count() / 60. << " min" << std::endl;
            NW.SaveWeights();

        }
        else {
            NW.ReadWeights();
        }
        std::cout << "Test? (1/0)\n";
        bool test_flag;
        std::cin >> test_flag;
        if (test_flag) {
            int ex_tests;
            data_info* data_test;
            data_test = ReadData("NewBaseTEST.txt", NW_config, ex_tests);
            right_answer = 0;
            for (int i = 0; i < ex_tests; i++) {
                NW.SetInput(data_test[i].pixels);
                predict = NW.ForwarFeed();
                right = data_test[i].digit;
                if (right == predict)
                    right_answer++;
            }
            std::cout << "right answer: " << right_answer / ex_tests * 100 << std::endl;
        }
        std::cout << "Repeat? (1/0)\n";
        std::cin >> repeat;
    }
}

