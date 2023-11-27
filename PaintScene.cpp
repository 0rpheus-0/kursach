#include "PaintScene.h"
#include <QWidget>
#include <QtWidgets>
#include <QPainter>
#include <iostream>


PaintScene::PaintScene(QWidget *parent)
    : QWidget(parent)
{
	ui.setupUi(this);
    setFocusPolicy(Qt::StrongFocus);
	draw = false;
}

void PaintScene::paintEvent(QPaintEvent*) {
    QPainter painter(this);
	QPalette Pal(palette());
    Pal.setColor(QPalette::Background, Qt::black);
    setAutoFillBackground(true);
    setPalette(Pal);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setPen(QPen(Qt::white, 12, Qt::SolidLine));
    for (int i = 0; i < vv.size(); i++)
        if (i > 0)
            painter.drawEllipse(vv[i - 1], 15, 15);

}

void PaintScene::mousePressEvent(QMouseEvent* pe) {
	draw = true;
}

void PaintScene::mouseMoveEvent(QMouseEvent* pe) {
	if (draw) {
        //std::cout<<"dr"<<std::endl;
		vv.push_back(pe->pos());
	}
	update();
}
void PaintScene::mouseReleaseEvent(QMouseEvent* pe) {
    std::cout<<"pic"<<std::endl;
	draw = false;
	QPixmap scr;
	scr = QPixmap::grabWidget(this);

    QFile mFile("D:/Proga/Qt/test.txt");
	mFile.open(QIODevice::WriteOnly);
	QTextStream fin(&mFile);

    std::cout<<"pic2"<<std::endl;
	QImage img;
	img = scr.toImage();
	img = img.scaled(28, 28);
	int w = img.size().width();
	int h = img.size().height();
	for (int i = 0; i < w; i++) {
		for (int j = 0; j < h; j++) {
            double tm = img.pixelColor(j, i).blue() / 255.;
            if(tm!=0)
                tm=1;
            fin << tm << " ";
		}
		fin << endl;
	}


	mFile.close();
}

void PaintScene::clear() {
	vv.clear();
    update();
}


