#ifndef LIGHT_H
#define LIGHT_H
#include <GL/glu.h>
#include <QGLWidget>
#include <QApplication>
#include <QtOpenGL>
#include <QKeyEvent>
class light : public QGLWidget
{
    Q_OBJECT
public:

    explicit light(QWidget *parent = 0);


protected:
   GLdouble m_xRotate;
    GLdouble m_yRotate;
QPoint m_ptPosition;
QVector<GLfloat> vecVertices;
QVector<GLfloat> vecTextures;
QVector<GLuint> vecIndices;
GLuint textureID[1]; 
void genTextures();
    void getIndexArray();
    void getVerTexArrays();
    void drawFigure();
    virtual void initializeGL();
    virtual void resizeGL(int nWidth, int nHeight);
    virtual void paintGL();
    virtual void keyPressEvent(QKeyEvent *);
    virtual void mousePressEvent(QMouseEvent *pe);
    virtual void mouseMoveEvent(QMouseEvent *pe);

private:
    GLUquadricObj* m_qObj;
signals:
    
public slots:
    
};
#endif // LIGHT_H
