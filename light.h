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

   GLfloat m_xRotate;
   GLfloat m_yRotate;
   GLfloat m_xGo;
   GLfloat m_yGo;
   GLfloat m_Rotate;
   QPoint m_ptPosition;
   void drawAxis();
   virtual void initializeGL();
   virtual void resizeGL(int nWidth, int nHeight);
   virtual void paintGL();
   virtual void keyPressEvent(QKeyEvent *);
   virtual void mousePressEvent(QMouseEvent *pe);
   virtual void mouseMoveEvent(QMouseEvent *pe);
   void defaultScene();
private:
    GLUquadricObj* m_qObj;
signals:

public slots:

};
#endif // LIGHT_H

