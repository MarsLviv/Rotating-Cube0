#include "mb22.h"

#include <QtGui>
#include <QMouseEvent>
#include <QScreen>
#include <GL/glu.h>
#include <math.h>
#include <locale.h>

MB22::MB22(QWidget *parent) : QGLWidget(parent), scale(0.5), counter(0), delay(50)
            , backgroundColor(215.0/255.0, 214.0/255.0, 213.0/255.0, 1.0), nObj(0) {
    boxes = new int[4];
    for (int i = 0; i < 8; i++){
        xRot[i] = 0; yRot[i] = 0; zRot[i] = 0;
    }
    zRot[1] = 90; yRot[2] = 180; yRot[3] = 90; zRot[4] = -90;// need rotate to be in
    zRot[5] = 180; xRot[6] = 180; zRot[7] = 180;    // decent position
    poss.plot2T();
}

MB22::~MB22(){
    delete boxes;
}

void MB22::setScale(GLfloat newScale){
    if (newScale > 1.0){
        scale = 1.0; return;
    }
    if (newScale < 0.2){
        scale = 0.2; return;
    }
    scale = newScale; return;
}

GLfloat MB22::getScale(){
    return scale;
}

void MB22::mousePressEvent(QMouseEvent *e){

    if (counter > 0)// forbidden picking until processing previous pick (press)
        return;

    mousePressPosition = QVector2D(e->localPos());

    QScreen *screen = QGuiApplication::primaryScreen();
    QPixmap pixmap = screen->grabWindow(winId());
    QRgb color = pixmap.toImage().pixel(e->x(), e->y());
    QColor color1 = pixmap.toImage().pixel(e->x(), e->y());
    qDebug() << "NEW PICK ";

    //  piked color in background
    if ( (color1.red() == backgroundColor.x() * 255 || color1.red() == backgroundColor.x() * 255 + 1 || color1.red() == backgroundColor.x() * 255 + 1) &&
        (color1.green() == backgroundColor.y() * 255 || color1.green() == backgroundColor.y() * 255 + 1 || color1.green() == backgroundColor.y() * 255 - 1) &&
        (color1.blue() == backgroundColor.z() * 255 || color1.blue() == backgroundColor.z() * 255 + 1 || color1.blue() == backgroundColor.z() * 255 - 1) ){
        qDebug() << "background";
        return;
    }

    if ( (color == 4278190080)// forbidden any color except black or any from surfaces
            || (color == 4294901760) || (color == 4278255360) || (color == 4294967040)
            || (color == 4294836224) || (color == 4294901248) || (color == 4278190335)
            || (color == 4294835456) || (color == 4278190334) || (color == 4294902015)
            || (color == 4278255104) || (color == 4294769664) || (color == 4294836478)
            || (color == 4294770688) || (color == 4278254848) || (color == 4294967295)
            || (color == 4294705152) || (color == 4278190333) || (color == 4294901502)
            || (color == 4294835709) || (color == 4294770941) || (color == 4278254592)
            || (color == 4278190332) || (color == 4294769916) || (color == 4294705404) ){
    ;} else
        return;

    if (color == 4278190080){   // piked black color in frame
        int tmp = 0;            // we going right in screen, while color of pixel == black
        while (color == 4278190080){qDebug() << "++tmp";
            color = pixmap.toImage().pixel(e->x() + ++tmp, e->y());
            color1 = pixmap.toImage().pixel(e->x() + ++tmp, e->y());
        }
    }
    // piked color in background.
    // need this check again.
    // because from black frame path can go to background
    if ( (color1.red() == backgroundColor.x() * 255 || color1.red() == backgroundColor.x() * 255 + 1 || color1.red() == backgroundColor.x() * 255 + 1) &&
        (color1.green() == backgroundColor.y() * 255 || color1.green() == backgroundColor.y() * 255 + 1 || color1.green() == backgroundColor.y() * 255 - 1) &&
        (color1.blue() == backgroundColor.z() * 255 || color1.blue() == backgroundColor.z() * 255 + 1 || color1.blue() == backgroundColor.z() * 255 - 1) ){
        qDebug() << "background from frame";
        return;
    }

    handlePickedColor(color);// calculate number [nObj] and it color [colorC] of picked box
    poss.picked(nObj, colorC);// calculate [face] and [boxes] to rotate
    face = poss.getFace();
    poss.getBoxes(boxes);
    qDebug() << "picked face" << face << "with boxes:" << boxes[0] << boxes[1] << boxes[2] << boxes[3];
    //poss.plot2T();

    for (int i = 0; i < 8; i++){
        xRot[i] = 0; yRot[i] = 0; zRot[i] = 0;
    }

    if(e->buttons() & Qt::RightButton){// rotate to counterClockWise
        poss.rotateCounterClockWise();// rotate data in table
        //poss.plot2T();

        for (int i = 0; i < 4; i++){// rotate all picked boxes
                if (face == 'F') zRot[boxes[i] - 1] = 10;
                if (face == 'B') zRot[boxes[i] - 1] = -10;
                if (face == 'L') xRot[boxes[i] - 1] = -10;
                if (face == 'R') xRot[boxes[i] - 1] = 10;
                if (face == 'T') yRot[boxes[i] - 1] = 10;
                if (face == 'D') yRot[boxes[i] - 1] = -10;
        }
    }

    if(e->buttons() & Qt::LeftButton){// rotate to ClockWise
        poss.rotateClockWise();// rotate data in table
        //poss.plot2T();

        for (int i = 0; i < 4; i++){// rotate all picked boxes
                if (face == 'F') zRot[boxes[i] - 1] = -10;
                if (face == 'B') zRot[boxes[i] - 1] = 10;
                if (face == 'L') xRot[boxes[i] - 1] = 10;
                if (face == 'R') xRot[boxes[i] - 1] = -10;
                if (face == 'T') yRot[boxes[i] - 1] = -10;
                if (face == 'D') yRot[boxes[i] - 1] = 10;
        }
    }

    counter = 9;
    timer.start(delay, this);

    for (int i = 0; i < 8; i++){
        xRotTMP[i] = xRot[i]; yRotTMP[i] = yRot[i]; zRotTMP[i] = zRot[i];
    }
}

void MB22::timerEvent(QTimerEvent *){
    if (counter > 0){
        for (int j = 0; j < 8; j++){
            xRot[j] = xRotTMP[j]; yRot[j] = yRotTMP[j]; zRot[j] = zRotTMP[j];
        }
        updateGL();
        counter--;
    }
    else {
        timer.stop();
    }
}

void MB22::setDelay(GLuint newDelay){
    if (newDelay < 1){
        delay = 1; return;
    }
    if (newDelay > 300){
        delay = 300; return;
    }
    delay = newDelay; return;
}

GLuint MB22::getDelay(){
    return delay;
}

void MB22::setBackgroundColor(QVector4D newBackgroundColor){
    backgroundColor = newBackgroundColor;
}

QVector4D MB22::getBackgroundColor(){
    return backgroundColor;
}

void MB22::mouseMoveEvent(QMouseEvent *e)
{
    if (counter > 0)// forbidden updating <updateGL();> while process rotating
        return;

    // Current mouse position - mouse press position
    QVector2D diff = QVector2D(e->localPos()) - mousePressPosition;

    // Rotation axis is perpendicular to the mouse trajectory
    QVector3D n = QVector3D(diff.y(), diff.x(), 0.0).normalized();

    // Rotation angle relative to the length of the mouse sweep
    qreal angle = diff.length() / 40;

    // New rotation axis
    rotationAxis = n.normalized();

    rotation = QQuaternion::fromAxisAndAngle(rotationAxis, angle) * rotation;
    updateGL();
}

void MB22::initializeGL()
{
    initializeGLFunctions();
    //glClearColor(215.0/256.0, 214.0/256.0, 213.0/256.0, 1.0);
    glClearColor(backgroundColor.x(), backgroundColor.y(),
                 backgroundColor.z(), backgroundColor.w());
    glShadeModel(GL_FLAT);// not works ???
    initShaders();

    // Enable depth buffer
    glEnable(GL_DEPTH_TEST);

    // Enable back face culling
    //glEnable(GL_CULL_FACE);

    geometries1.init();
    geometries2.init();
    geometries3.init();
    geometries4.init();
    geometries5.init();
    geometries6.init();
    geometries7.init();
    geometries8.init();

    //timer.start(30, this);
}

void MB22::initShaders()
{
    // Override system locale until shaders are compiled
    setlocale(LC_NUMERIC, "C");

    // Compile vertex shader
    if (!program.addShaderFromSourceFile(QGLShader::Vertex, ":/vshader.glsl"))
        close();

    // Compile fragment shader
    if (!program.addShaderFromSourceFile(QGLShader::Fragment, ":/fshader.glsl"))
        close();

    // Link shader pipeline
    if (!program.link())
        close();

    // Bind shader pipeline for use
    if (!program.bind())
        close();

    // Restore system locale
    setlocale(LC_ALL, "");
}

void MB22::resizeGL(int w, int h){
    glViewport(0, 0, w, h);

    // aspect ratio
    qreal aspect = qreal(w) / qreal(h ? h : 1);

    const qreal zNear = 3.0, zFar = 12.0, fov = 45.0;

    // Reset projection
    projection.setToIdentity();

    // Set perspective projection
    projection.perspective(fov, aspect, zNear, zFar);
}

void MB22::paintGL(){
    // Clear color and depth buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    drawBox();
}

void MB22::drawBox(){
    QMatrix4x4 matrix1;
    matrix1.translate(0.0, 0.0, -5.0);
    QQuaternion result1 =   rotXYZangle(QVector3D(1.0, 0.0, 0.0), xRot[0]) *
                            rotXYZangle(QVector3D(0.0, 1.0, 0.0), yRot[0]) *
                            rotXYZangle(QVector3D(0.0, 0.0, 1.0), zRot[0]);
    rotation1 = result1 * rotation1;
    matrix1.rotate(rotation * rotation1);
    matrix1.translate(1.0 * scale, 1.0 * scale, 1.0 * scale);
    program.setUniformValue("mvp_matrix", projection * matrix1);// Send modelview-projection
                                                    // matrix to shader using "mvp_matrix"
    geometries1.drawGeometry(&program);// Draw cube geometry

    QMatrix4x4 matrix2;
    matrix2.translate(0.0, 0.0, -5.0 );
    QQuaternion result2 =   rotXYZangle(QVector3D(1.0, 0.0, 0.0), xRot[1]) *
                            rotXYZangle(QVector3D(0.0, 1.0, 0.0), yRot[1]) *
                            rotXYZangle(QVector3D(0.0, 0.0, 1.0), zRot[1]);
    rotation2 = result2 * rotation2;
    matrix2.rotate(rotation * rotation2);
    matrix2.translate(1.0 * scale, 1.0 * scale, 1.0 * scale);
    program.setUniformValue("mvp_matrix", projection * matrix2);
    geometries2.drawGeometry(&program);

    QMatrix4x4 matrix3;
    matrix3.translate(0.0, 0.0, -5.0);
    QQuaternion result3 =   rotXYZangle(QVector3D(1.0, 0.0, 0.0), xRot[2]) *
                            rotXYZangle(QVector3D(0.0, 1.0, 0.0), yRot[2]) *
                            rotXYZangle(QVector3D(0.0, 0.0, 1.0), zRot[2]);
    rotation3 = result3 * rotation3;
    matrix3.rotate(rotation * rotation3);
    matrix3.translate(1.0 * scale, 1.0 * scale, 1.0 * scale);
    program.setUniformValue("mvp_matrix", projection * matrix3);
    geometries3.drawGeometry(&program);

    QMatrix4x4 matrix4;
    matrix4.translate(0.0, 0.0, -5.0);
    QQuaternion result4 =   rotXYZangle(QVector3D(1.0, 0.0, 0.0), xRot[3]) *
                            rotXYZangle(QVector3D(0.0, 1.0, 0.0), yRot[3]) *
                            rotXYZangle(QVector3D(0.0, 0.0, 1.0), zRot[3]);
    rotation4 = result4 * rotation4;
    matrix4.rotate(rotation * rotation4);
    matrix4.translate(1.0 * scale, 1.0 * scale, 1.0 * scale);
    program.setUniformValue("mvp_matrix", projection * matrix4);
    geometries4.drawGeometry(&program);

    QMatrix4x4 matrix5;
    matrix5.translate(0.0, 0.0, -5.0);
    QQuaternion result5 =   rotXYZangle(QVector3D(1.0, 0.0, 0.0), xRot[4]) *
                            rotXYZangle(QVector3D(0.0, 1.0, 0.0), yRot[4]) *
                            rotXYZangle(QVector3D(0.0, 0.0, 1.0), zRot[4]);
    rotation5 = result5 * rotation5;
    matrix5.rotate(rotation * rotation5);
    matrix5.translate(1.0 * scale, 1.0 * scale, 1.0 * scale);
    program.setUniformValue("mvp_matrix", projection * matrix5);
    geometries5.drawGeometry(&program);

    QMatrix4x4 matrix6;
    matrix6.translate(0.0, 0.0, -5.0);
    QQuaternion result6 =   rotXYZangle(QVector3D(1.0, 0.0, 0.0), xRot[5]) *
                            rotXYZangle(QVector3D(0.0, 1.0, 0.0), yRot[5]) *
                            rotXYZangle(QVector3D(0.0, 0.0, 1.0), zRot[5]);
    rotation6 = result6 * rotation6;
    matrix6.rotate(rotation * rotation6);
    matrix6.translate(1.0 * scale, 1.0 * scale, 1.0 * scale);
    program.setUniformValue("mvp_matrix", projection * matrix6);
    geometries6.drawGeometry(&program);

    QMatrix4x4 matrix7;
    matrix7.translate(0.0, 0.0, -5.0);
    QQuaternion result7 =   rotXYZangle(QVector3D(1.0, 0.0, 0.0), xRot[6]) *
                            rotXYZangle(QVector3D(0.0, 1.0, 0.0), yRot[6]) *
                            rotXYZangle(QVector3D(0.0, 0.0, 1.0), zRot[6]);
    rotation7 = result7 * rotation7;
    matrix7.rotate(rotation * rotation7);
    matrix7.translate(1.0 * scale, 1.0 * scale, 1.0 * scale);
    program.setUniformValue("mvp_matrix", projection * matrix7);
    geometries7.drawGeometry(&program);

    QMatrix4x4 matrix8;
    matrix8.translate(0.0, 0.0, -5.0);
    QQuaternion result8 =   rotXYZangle(QVector3D(1.0, 0.0, 0.0), xRot[7]) *
                            rotXYZangle(QVector3D(0.0, 1.0, 0.0), yRot[7]) *
                            rotXYZangle(QVector3D(0.0, 0.0, 1.0), zRot[7]);
    rotation8 = result8 * rotation8;
    matrix8.rotate(rotation * rotation8);
    matrix8.translate(1.0 * scale, 1.0 * scale, -1.0 * scale);
    program.setUniformValue("mvp_matrix", projection * matrix8);
    geometries8.drawGeometry(&program);

    for (int i = 0; i < 8; i++){// after each 10 deg rotation clears data. But initial
        xRot[i] = 0; yRot[i] = 0; zRot[i] = 0; // data contain x(yz)RotTMP
    }
}

QQuaternion MB22::rotXYZangle(QVector3D XYZ, int angle){
    QQuaternion rotation = QQuaternion::fromAxisAndAngle(XYZ.normalized(), angle);
    return rotation;
}

void MB22::handlePickedColor(QRgb color){
    // 1 red 4294901760 gre 4278255360 yel 4294967040
    // 2 red 4294836224 yel 4294901248 blu 4278190335
    // 3 yel 4294835456 blu 4278190334 mag 4294902015
    // 4 gre 4278255104 yel 4294769664 mag 4294836478
    // 5 red 4294770688 gre 4278254848 whi 4294967295
    // 6 red 4294705152 blu 4278190333 whi 4294901502
    // 7 whi 4294835709 mag 4294770941 gre 4278254592
    // 8 blu 4278190332 whi 4294769916 mag 4294705404
    if (color == 4294901760 || color == 4278255360 || color == 4294967040){   // 1 box
        nObj = 1;                           // get number and it color of picked box
        if (color == 4294901760) colorC = 'r';
        else if (color == 4278255360) colorC = 'g';
        else colorC = 'y';
    }
    if (color == 4294836224 || color == 4294901248 || color == 4278190335){   // 2 box
        nObj = 2;
        if (color == 4294836224) colorC = 'r';
        else if (color == 4294901248) colorC = 'y';
        else colorC = 'b';
    }
    if (color == 4294835456 || color == 4278190334 || color == 4294902015){   // 3 box
        nObj = 3;
        if (color == 4294835456) colorC = 'y';
        else if (color == 4278190334) colorC = 'b';
        else colorC = 'm';
    }
    if (color == 4278255104 || color == 4294769664 || color == 4294836478){   // 4 box
        nObj = 4;
        if (color == 4278255104) colorC = 'g';
        else if (color == 4294769664) colorC = 'y';
        else colorC = 'm';
    }
    if (color == 4294770688 || color == 4278254848 || color == 4294967295){   // 5 box
        nObj = 5;
        if (color == 4294770688) colorC = 'r';
        else if (color == 4278254848) colorC = 'g';
        else colorC = 'w';
    }
    if (color == 4294705152 || color == 4278190333 || color == 4294901502){   // 6 box
        nObj = 6;
        if (color == 4294705152) colorC = 'r';
        else if (color == 4278190333) colorC = 'b';
        else colorC = 'w';
    }
    if (color == 4294835709 || color == 4294770941 || color == 4278254592){   // 7 box
        nObj = 7;
        if (color == 4294835709) colorC = 'w';
        else if (color == 4294770941) colorC = 'm';
        else colorC = 'g';
    }
    if (color == 4278190332 || color == 4294769916 || color == 4294705404){   // 8 box
        nObj = 8;
        if (color == 4278190332) colorC = 'b';
        else if (color == 4294769916) colorC = 'w';
        else colorC = 'm';
    }
    qDebug() << "picked" << nObj << "-st obj. with color" << color << " " << colorC;
}
