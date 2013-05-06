#ifndef SCENE3D_H
#define SCENE3D_H

#include <QGLWidget>

class Scene3D : public QGLWidget
{
private:
    GLfloat xRot;
    GLfloat yRot;
    GLfloat zRot;
    GLfloat zTra;
    GLfloat nSca;

    QPoint ptrMousePosition;

    void scale_plus();
    void scale_minus();
    void rotate_up();
    void rotate_down();
    void rotate_right();
    void rotate_left();
    void translate_up();
    void translate_down();
    void defaultScene();

    void drawAxis();

    void getVertexArray();
    void getColorArray();
    void getIndexArray();
    void drawFigure();

protected:
    virtual void initializeGL();
    virtual void resizeGL(int w, int h);
    virtual void paintGL();

    virtual void mousePressEvent(QMouseEvent *pe);
    virtual void mouseMoveEvent(QMouseEvent *pe);
    virtual void mouseReleaseEvent(QMouseEvent *pe);
    virtual void keyPressEvent(QKeyEvent *pe);
    virtual void wheelEvent(QWheelEvent *pe);

public:
     Scene3D(QWidget *parent = 0);
    
signals:
    
public slots:
    
};

#endif // SCENE3D_H
