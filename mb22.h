#ifndef MB22_H
#define MB22_H

#include "geometry.h"

#include <QGLWidget>
#include <QGLFunctions>
#include <QMatrix4x4>
#include <QQuaternion>
#include <QVector2D>
#include <QVector3D>
#include <QBasicTimer>
#include <QGLShaderProgram>
#include <QBasicTimer>

#include <positions.h>

class Geometry;

class MB22 : public QGLWidget, protected QGLFunctions {
public:
    MB22(QWidget *parent = 0);
    ~MB22();

    void setScale(GLfloat newScale);// scale of magic box
    GLfloat getScale();

    void setDelay(GLuint newDelay);// in msec
    GLuint getDelay();

    void setFrameThickness(GLfloat newFrame);
    GLfloat getFrameThickness();

    void setBackgroundColor(QVector4D newBackgroundColor);
    QVector4D getBackgroundColor();

protected:
    void mousePressEvent(QMouseEvent *e);
    void mouseMoveEvent (QMouseEvent* e);

    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();

    void initShaders();

    void drawBox();
    void timerEvent(QTimerEvent *e);

private:
    QGLShaderProgram program;
    Geometry geometries1{QVector3D(255/255, 0.0, 0.0), QVector3D(0.0, 255/255, 0.0), QVector3D(255/255, 255/255, 0.0)};
    Geometry geometries2{QVector3D(254.0/255.0, 0.0, 0.0), QVector3D(254.0/255.0, 254.0/255.0, 0.0), QVector3D(0.0, 0.0, 1.0)};
    //                              magenta
    Geometry geometries3{QVector3D(1.0, 0.0, 1.0), QVector3D(0.0, 0.0, 254.0/255.0), QVector3D(253.0/255.0, 253.0/255.0, 0.0)};
    //                                                      magenta
    Geometry geometries4{QVector3D(0.0, 254.0/255.0, 0.0), QVector3D(254.0/255.0, 0.0, 254.0/255.0), QVector3D(252.0/255.0, 252.0/255.0, 0.0)};

    Geometry geometries5{QVector3D(253.0/255.0, 0.0, 0.0), QVector3D(1.0, 1.0, 1.0), QVector3D(0.0, 253.0/255.0, 0.0)};
    Geometry geometries6{QVector3D(252.0/255.0, 0.0, 0.0), QVector3D(0.0, 0.0, 253.0/255.0), QVector3D(254.0/255.0, 254.0/255.0, 254.0/255.0)};
    Geometry geometries7{QVector3D(253.0/255.0, 0.0, 253.0/255.0), QVector3D(0.0, 252.0/255.0, 0.0), QVector3D(253.0/255.0, 253.0/255.0, 253.0/255.0)};
    Geometry geometries8{QVector3D(0.5f, 0.5f, 0.5f), QVector3D(0.0, 0.0, 252.0/255.0), QVector3D(252.0/255.0, 252.0/255.0, 252.0/255.0), QVector3D(252.0/255.0, 0.0, 252.0/255.0)};

    QMatrix4x4 projection;

    QVector2D mousePressPosition;
    QVector3D rotationAxis;
    QQuaternion rotation;
    QQuaternion rotation1, rotation2, rotation3, rotation4,
        rotation5, rotation6, rotation7, rotation8;

    GLfloat scale;// scale of magic box

    Positions poss;
    int xRot[8], yRot[8], zRot[8];// contain separately each rotation (Ox, Oy, Oz) of each box (0-7)
    int xRotTMP[8], yRotTMP[8], zRotTMP[8];// after small 10 deg rotation data in x(yz)Rot clears
                                           // here we contain this data
    char face;  // ['F'..'D'] this face was picked
    int *boxes; // [1..8] these boxes placed in picked face.

    QQuaternion rotXYZangle(QVector3D XYZ, int angle);

    char colorC;
    int nObj;
    void handlePickedColor(QRgb color);// calculate number [nObj] and
                                       // it color [colorC] of picked box

    QBasicTimer timer;// each small rotation delay with timer
    long long int counter;// each 90 deg rotation divided on 9 smaller rotations per 10 deg
    // it counts this small rotations

    GLuint delay;// affects on angular rotation

    QVector4D backgroundColor;
};

#endif // MB22_H
