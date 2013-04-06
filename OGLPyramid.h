#ifndef _OGLPYRAMID_H_
#define _OGLPYRAMID_H_

#include <QGLWidget>
#include <QMouseEvent>
#include <QApplication>

class OGLPyramid : public QGLWidget {
private:
    GLuint m_nPyramid;
    GLfloat m_xRotate;
    GLfloat m_yRotate;
    GLfloat m_xTimerRotate;
    QPoint m_ptPosition;
    GLdouble turnRightLeft,turnUpDown, turnFar, speed;

protected:
    virtual void initializeGL();
    virtual void resizeGL(int nWidth, int nHeight);
    virtual void paintGL();
    virtual void mousePressEvent(QMouseEvent *pe);
    virtual void mouseMoveEvent(QMouseEvent *pe);
    virtual void timerEvent(QTimerEvent *te);
    virtual void keyPressEvent(QKeyEvent *);
    GLuint createPyramid(GLfloat fSize = 5.0f);
public:
    OGLPyramid(QWidget *pwgt = 0);


};



#endif // _OGLPYRAMID_H_
