#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "ui_mainwindow.h"
#include "PaintScene.h"
#include "NetWork.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
    PaintScene* PS;
    NetWork NW;
    data_NetWork NW_config;

public:
    MainWindow(QWidget *parent = nullptr);
    data_NetWork ReadDataNetWork(std::string path);
    void ReadTest(double* input, int input_n);
    //~MainWindow();

signals:
    void endWriteToFile();
public slots:
    void StartGuess();
    void clearLCD();
private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
