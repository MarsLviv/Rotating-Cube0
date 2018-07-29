#include "mainwindow.h"

#include <QtGui>

MainWindow::MainWindow(QWidget *parent) {
    createBox();
}

MainWindow::~MainWindow(){
}

void MainWindow::createBox(){
    qDebug() << "createBox()";
    oglBox = new MB22();
    oglBox->setCursor(Qt::CrossCursor);
    QMainWindow::setCentralWidget(oglBox);
}
