
#ifndef _OGLPYRAMID_H_
#define _OGLPYRAMID_H_

#include <QGLWidget>
#include <QMouseEvent>

class OGLPyramid : public QGLWidget {
private:
    GLuint m_nPyramid;
    GLfloat m_xRotate;
    GLfloat m_yRotate;
    QPoint m_ptPosition;
protected:
    virtual void initializeGL();
    virtual void resizeGL(int nWidth, int nHeight);
    virtual void paintGL();
    virtual void mousePressEvent(QMouseEvent *pe);
    virtual void mouseMoveEvent(QMouseEvent *pe);
    GLuint createPyramid(GLfloat fSize = 1.0f);
public:
    OGLPyramid(QWidget *pwgt = 0);
};

#endif // _OGLPYRAMID_H_
