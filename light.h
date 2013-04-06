#ifndef LIGHT_H
#define LIGHT_H
#include <GL/glu.h>
#include <QGLWidget>
#include <QApplication>
#include <QKeyEvent>

class light : public QGLWidget
{
    Q_OBJECT
public:

    explicit light(QWidget *parent = 0);
    /*void init(void);
    void display(void);
    void reshape(int w, int h);*/
protected:
    virtual void initializeGL();
    virtual void resizeGL(int nWidth, int nHeight);
    virtual void paintGL();
    virtual void keyPressEvent(QKeyEvent *);
private:
    GLUquadricObj* m_qObj;
signals:
    
public slots:
    
};

#endif // LIGHT_H
