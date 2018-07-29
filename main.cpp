// ROTATING CUBE USING OpenGL/QUATERNION/SHADERS

/* project was made in Qt 5.2.0 on Ubuntu 16.4  2018.06.25
 *
 * after Qt installation were used these commands:
 * sudo apt-get install build-essential // Install g++
 * sudo apt-get install libfontconfig1  // install fonts
 * sudo apt-get install mesa-common-dev // install OpenGL libraries
 * sudo apt-get install libglu1-mesa-dev -y // sometime you need it
 * */

#include <QApplication>
#include <QLabel>
#include <QtWidgets>

#ifndef QT_NO_OPENGL
#include "mainwindow.h"
#endif

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    app.setApplicationName("Rotating cube");
#ifndef QT_NO_OPENGL
    MainWindow widget;
    int width = 710;
    int height = 710;
    widget.move((QApplication::desktop()->width() - width) / 2 ,
           (QApplication::desktop()->height() - height) / 2);
    widget.setMinimumWidth(width);
    widget.setMinimumHeight(height);
    widget.setWindowTitle("Rubik's cube 2x2 v. 0.5");
    widget.show();
#else
    QLabel note("You need OpenGL Support");
    note.show();
#endif
    return app.exec();
}
