#ifndef _OGLQUAD_H_
#define _OGLQUAD_H_

#include <QGLWidget>

class OGLQuad : public QGLWidget {
protected:
    virtual void initializeGL ();
    virtual void resizeGL (int nWidth, int nHeight);
    virtual void paintGL ();
public:
    OGLQuad (QWidget *pwgt = 0);
};

#endif // _OGLQUAD_H_
