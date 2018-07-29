#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QGLWidget>
#include <QMainWindow>
#include "mb22.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    MB22 * oglBox;

protected:

private:
    void createBox();
};

#endif // MAINWIDGET_H
