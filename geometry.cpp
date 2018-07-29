#include "geometry.h"
#include <QVector3D>

Geometry::Geometry() : scale(0.5), frameThickness(0.9){
}

Geometry::Geometry(QVector3D a, QVector3D b, QVector3D c) :
    faceA(a), faceB(b), faceC(c), flag(0), scale(0.5), frameThickness(0.9){
}

Geometry::Geometry(QVector3D a, QVector3D b, QVector3D c, QVector3D d) :
    faceA(a), faceB(b), faceC(c), faceD(d), flag(1), scale(0.5), frameThickness(0.9){
}

Geometry::~Geometry(){
    glDeleteBuffers(2, vboIds);
}

void Geometry::init()
{
    initializeGLFunctions();

    // Generate 2 VBOs
    glGenBuffers(2, vboIds);

    // Initializes geometry and transfers it to VBOs
    initGeometry();
}

void Geometry::initGeometry(){
    GLfloat border = frameThickness; // frame width
    GLfloat borderZ = 0.999; // distanse between colored and black faces
    QVector3D faceK = QVector3D(0.5f, 0.5f, 0.5f);// color for inner faces
    QVector3D faceBL = QVector3D(0.0f, 0.0f, 0.0f);// color for frame
    QVector3D vertices[] = {
         QVector3D(-1.0 * border, -1.0 * border,  1.0) * scale, faceA , // v0 front face - red
         QVector3D(1.0 * border, -1.0 * border,  1.0) * scale,  faceA , // v1
         QVector3D(-1.0 * border,  1.0 * border,  1.0) * scale, faceA , // v2
         QVector3D(1.0 * border,  1.0 * border,  1.0) * scale,  faceA , // v3

         QVector3D(1.0 * border, -1.0 * border, -1.0) * scale,  faceK, //  v4 back face
         QVector3D(-1.0 * border, -1.0 * border, -1.0) * scale, faceK,  // v5
         QVector3D(1.0 * border,  1.0 * border, -1.0) * scale,  faceK, //  v6
         QVector3D(-1.0 * border,  1.0 * border, -1.0) * scale, faceK, //  v7

         QVector3D(1.0, -1.0 * border,  1.0 * border) * scale,  faceB , // v8 (1 again) right face - green
         QVector3D(1.0, -1.0 * border, -1.0 * border) * scale,  faceB, //  v9 (4 again)
         QVector3D(1.0,  1.0 * border, -1.0 * border) * scale,  faceB, //  v10 (6 again)
         QVector3D(1.0,  1.0 * border,  1.0 * border) * scale,  faceB, //  v11 (3 again)

         QVector3D(-1.0, -1.0 * border,  1.0 * border) * scale, faceK , // v12 (0 again) left face - yellow
         QVector3D(-1.0,  1.0 * border,  1.0 * border) * scale, faceK , // v13 (2 again)
         QVector3D(-1.0,  1.0 * border, -1.0 * border) * scale, faceK, //  v14 (7 again)
         QVector3D(-1.0, -1.0 * border, -1.0 * border) * scale, faceK,  // v15 (5 again)

         QVector3D(-1.0 * border,  1.0,  1.0 * border) * scale, faceC , // v16 (2 again) top face - magenta
         QVector3D(1.0 * border,  1.0,  1.0 * border) * scale,  faceC , // v17 (3 again)
         QVector3D(1.0 * border,  1.0, -1.0 * border) * scale,  faceC, //  v18 (6 again)
         QVector3D(-1.0 * border,  1.0, -1.0 * border) * scale, faceC, //  v19 (7 again)

         QVector3D(-1.0 * border, -1.0,  1.0 * border) * scale, faceK , // v20 (0 again) bottom face - cyan
         QVector3D(1.0 * border, -1.0,  1.0 * border) * scale,  faceK , // v21 (1 again)
         QVector3D(1.0 * border, -1.0, -1.0 * border) * scale,  faceK, //  v22 (4 again)
         QVector3D(-1.0 * border, -1.0, -1.0 * border) * scale, faceK,  // v23 (5 again)

        QVector3D(-1.0, -1.0,  1.0 * borderZ) * scale, faceBL , // v24 (v0) front face - BLACK
        QVector3D(1.0, -1.0,  1.0 * borderZ) * scale,  faceBL , // v25 (v1)
        QVector3D(-1.0,  1.0,  1.0 * borderZ) * scale, faceBL , // v26 (v2)
        QVector3D(1.0,  1.0,  1.0 * borderZ) * scale,  faceBL , // v27 (v3)

        QVector3D(1.0 * borderZ, -1.0,  1.0) * scale,  faceBL , // v28 (v8, 1 again) right face - BLACK
        QVector3D(1.0 * borderZ, -1.0, -1.0) * scale,  faceBL, //  v29 (v9, 4 again)
        QVector3D(1.0 * borderZ,  1.0, -1.0) * scale,  faceBL, //  v30 (v10, 6 again)
        QVector3D(1.0 * borderZ,  1.0,  1.0) * scale,  faceBL, //  v31 (v11, 3 again)

        QVector3D(-1.0,  1.0 * borderZ,  1.0) * scale, faceBL , // v32 (v16 2 again) top face - BLACK
        QVector3D(1.0,  1.0 * borderZ,  1.0) * scale,  faceBL , // v33 (v17 3 again)
        QVector3D(1.0,  1.0 * borderZ, -1.0) * scale,  faceBL, //  v34 (v18 6 again)
        QVector3D(-1.0,  1.0 * borderZ, -1.0) * scale, faceBL, //  v35 (v19 7 again)

        QVector3D(1.0, -1.0, -1.0 * borderZ) * scale,  faceBL, //  v36 (v4) back face - BLACK
        QVector3D(-1.0, -1.0, -1.0 * borderZ) * scale, faceBL,  // v37 (v5)
        QVector3D(1.0,  1.0, -1.0 * borderZ) * scale,  faceBL, //  v38 (v6)
        QVector3D(-1.0,  1.0, -1.0 * borderZ) * scale, faceBL, //  v39 (v7)

        QVector3D(-1.0 * borderZ, -1.0,  1.0) * scale, faceBL , // v40 (v12 0 again) left face - BLACK
        QVector3D(-1.0 * borderZ,  1.0,  1.0) * scale, faceBL , // v41 (v13 2 again)
        QVector3D(-1.0 * borderZ,  1.0, -1.0) * scale, faceBL, //  v42 (v14 7 again)
        QVector3D(-1.0 * borderZ, -1.0, -1.0) * scale, faceBL, //  v43 (v15 5 again)

        QVector3D(-1.0, -1.0 * borderZ,  1.0) * scale, faceBL , // v44 (v20 0 again) bottom face - BLACK
        QVector3D(1.0, -1.0 * borderZ,  1.0) * scale,  faceBL , // v45 (v21 1 again)
        QVector3D(1.0, -1.0 * borderZ, -1.0) * scale,  faceBL, //  v46 (v22 4 again)
        QVector3D(-1.0, -1.0 * borderZ, -1.0) * scale, faceBL  //  v47 (v23 5 again)
    };
    if (flag){
        vertices[9] = faceD;vertices[11] = faceD;vertices[13] = faceD;vertices[15] = faceD;
        vertices[1] = faceK;vertices[3] = faceK;vertices[5] = faceK;vertices[7] = faceK;
    }

    GLushort indices[] = {
        0, 1, 3, 2   // front face
        , 4, 5, 7, 6 // back face
        , 8, 9, 10, 11// right face
        ,12, 13, 14, 15// left face
        ,16, 17, 18, 19// top face
        ,20, 21, 22, 23// bottom face
        ,24, 25, 27, 26 // front face BLACK
        ,28, 29, 30, 31// right face BLACK
        ,32, 33, 34, 35// top face BLACK
        ,36, 37, 39, 38// back face BLACK
        ,40, 41, 42, 43// left face BLACK
        ,44, 45, 46, 47// left face BLACK
    };

    // Transfer vertex data to VBO 0
    glBindBuffer(GL_ARRAY_BUFFER, vboIds[0]);
    glBufferData(GL_ARRAY_BUFFER, ((6 * 8 + 48) * sizeof(QVector3D)), vertices, GL_STATIC_DRAW);

    // Transfer index data to VBO 1
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboIds[1]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, ((6 * 4 + 24) * sizeof(GLushort)), indices, GL_STATIC_DRAW);
}

void Geometry::drawGeometry(QGLShaderProgram *program)
{
    // Tell OpenGL which VBOs to use
    glBindBuffer(GL_ARRAY_BUFFER, vboIds[0]);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboIds[1]);

    // Offset for position
    quintptr offset = 0;

    // Tell OpenGL programmable pipeline how to locate vertex position data
    int vertexLocation = program->attributeLocation("a_position");// get pointer to DATA "a_position"
    program->enableAttributeArray(vertexLocation);
    glVertexAttribPointer(vertexLocation, 3, GL_FLOAT, GL_FALSE, 2 * sizeof(QVector3D), (const void *)offset);

    // Offset for vertex coordinate
    offset += sizeof(QVector3D);

    // Tell OpenGL programmable pipeline how to locate vertex color data
    int colorLocation = program->attributeLocation("a_color");
    program->enableAttributeArray(colorLocation);
    glVertexAttribPointer(colorLocation, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (const void *)offset);

    // Draw cube geometry using indices from VBO 1
    glDrawElements(GL_QUADS, (6 * 4 + 24), GL_UNSIGNED_SHORT, 0);
}

void Geometry::setScale(GLfloat newScale){
    if (newScale > 1.0){
        scale = 1.0; return;
    }
    if (newScale < 0.2){
        scale = 0.2; return;
    }
    scale = newScale; return;
}

GLfloat Geometry::getScale(){
    return scale;
}

void Geometry::setFrameThickness(GLfloat newFrameThickness){
    if (newFrameThickness > 1.0){
        frameThickness = 1.0; return;
    }
    if (newFrameThickness < 0.6){
        frameThickness = 0.6; return;
    }
    frameThickness = newFrameThickness; return;
}

GLfloat Geometry::getFrameThickness(){
    return frameThickness;
}

