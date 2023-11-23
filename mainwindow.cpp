#include "mainwindow.h"
#include "./ui_mainwindow.h"

data_NetWork MainWindow::ReadDataNetWork(std::string path) {
    data_NetWork data{};
    std::ifstream fin;
    fin.open(path);
    if (!fin.is_open()) {
        std::cout << "Error reading the file";
        system("pause");
    }
    else
        std::cout << path << " loading...\n";
    std::string tmp;
    int n;
    while (!fin.eof()) {
        fin >> tmp;
        if (tmp == "NetWork") {
            fin >> n;
            data.L = n;
            data.size = new int[n];
            for (int i = 0; i < n; i++) {
                fin >> data.size[i];
            }
        }
    }
    fin.close();
    return data;
}


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    //, ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    setWindowTitle("Мяу - мяу :");
    setWindowIcon(QIcon("D:/Proga/Qt/happy.png"));
    QWidget* MyWidget = new QWidget(this);

    MyWidget->setLayout(ui->gridLayout_2);//ui.gridLayout_2
    setCentralWidget(MyWidget);
    resize(500, 380);
    NW_config = ReadDataNetWork("D:/Proga/Qt/Config.txt");
    NW.Init(NW_config);
    NW.ReadWeights();
    ui->lcdNumber->display("");
}


void MainWindow::clearLCD() {
    ui->lcdNumber->display("");
}

void MainWindow::ReadTest(double* input, int input_n) {

    QFile mFile("D:/Proga/Qt/test.txt");
    mFile.open(QIODevice::ReadOnly);
    QTextStream fin(&mFile);
    if (mFile.isOpen())
        for (int j = 0; j < input_n; j++)
            fin >> input[j];
    else QMessageBox::information(0, "Error", "Error reading the file");
    mFile.close();
}

void MainWindow::StartGuess() {
    //double* input = new double[NW_config.size[0]];
    double* input = new double[784];
    //ReadTest(input, NW_config.size[0]);
    ReadTest(input, 784);
    NW.SetInput(input);
    double digit = NW.ForwarFeed();
    ui->lcdNumber->display(QString().setNum(digit));
}

/*
MainWindow::~MainWindow()
{
    delete ui;
}
*/
