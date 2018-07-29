#ifndef GEOMETRY_H
#define GEOMETRY_H

#include <QGLFunctions>
#include <QGLShaderProgram>
#include <QVector3D>

class Geometry : protected QGLFunctions
{
public:
    Geometry();
    Geometry(QVector3D a, QVector3D b, QVector3D c);
    Geometry(QVector3D a, QVector3D b, QVector3D c, QVector3D d);// need to draw 8-th box
    virtual ~Geometry();

    void init();
    void drawGeometry(QGLShaderProgram *program);

    void setScale(GLfloat newScale);// scale of magic box
    GLfloat getScale();

    void setFrameThickness(GLfloat newFrameThickness);// black Frame Thickness of magic box
    GLfloat getFrameThickness();

private:
    void initGeometry();

    GLuint vboIds[2];

    QVector3D faceA, faceB, faceC, faceD;
    int flag;// flag for using faceD

    GLfloat scale;
    GLfloat frameThickness;
};

#endif // GEOMETRY_H
