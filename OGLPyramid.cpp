#include "OGLPyramid.h"

OGLPyramid::OGLPyramid(QWidget *pwgt/*= 0*/)
    : QGLWidget(pwgt), m_xRotate(0), m_yRotate(0),m_xTimerRotate(0),turnFar(0),turnRightLeft(0),turnUpDown(0), speed(1) {
}

void OGLPyramid::initializeGL() {
    qglClearColor(Qt::black);
    glEnable(GL_DEPTH_TEST);
    glShadeModel(GL_FLAT);
    m_nPyramid = createPyramid(35.0f);
    startTimer(20);
}

void OGLPyramid::resizeGL(int nWidth, int nHeight) {
    //glViewport(0-4.5*(GLint)nWidth, 0-4.5*(GLint)nHeight, (GLint)nWidth*10, (GLint)nHeight*10);
    glViewport(0, 0, (GLint)nWidth, (GLint)nHeight);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    //GLfloat left=-0.2,right=0.2,bottom=-0.1125,top=0.1125,near=1.0,far=50.0;
    //GLfloat left=-(GLint)nWidth/2,right=(GLint)nWidth,bottom=-(GLint)nHeight,top=(GLint)nHeight,near=1.0,far=50.0;
    GLfloat left=-16.5,right=16.5,bottom=-10,top=10,near=50.0,far=4000.0;
    glFrustum(left, right, bottom, top, near, far);

}

void OGLPyramid::paintGL() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(0.0+turnRightLeft, 0.0+turnUpDown, -40.0+turnFar);

    glRotatef(m_xRotate+m_xTimerRotate, 1.0, 0.0, 0.0);
    glRotatef(m_yRotate+m_xTimerRotate, 0.0, 1.0, 0.0);

    /* //gluLookAt(0.0,0.0,5.0,0.0,0.0,0.0,0.0,1.0,0.0);

    //Модельная трансформация
    glScalef(1.0,2.0,1.0);*/
    glCallList(m_nPyramid);

}


void OGLPyramid::mousePressEvent(QMouseEvent *pe) {
    m_ptPosition = pe->pos();
}

void OGLPyramid::mouseMoveEvent(QMouseEvent *pe) {
    m_xRotate += 180 * (GLfloat)(pe->y() - m_ptPosition.y()) / height();
    m_yRotate += 180 * (GLfloat)(pe->x() - m_ptPosition.x()) / width();
    updateGL();

    m_ptPosition = pe->pos();
}
void OGLPyramid::timerEvent(QTimerEvent *)
{

    m_xTimerRotate+=1;
    updateGL();
}
void OGLPyramid::keyPressEvent(QKeyEvent *pe){
    switch(pe->key()){
    case Qt::Key_W:
        if(pe->modifiers() & Qt::ShiftModifier){
            turnUpDown-=speed;
        }
        else{
            turnFar+=speed;

        }
        break;
   case Qt::Key_S:
        if(pe->modifiers() & Qt::ShiftModifier){
            turnUpDown+=speed;
        }
        else{

            turnFar-=speed;
        }
        break;
    case Qt::Key_A:


            turnRightLeft+=speed;



        break;
    case Qt::Key_D:

             turnRightLeft-=speed;


        break;
    case Qt::Key_Escape:
       //emit exit();
        QApplication::exit();
        break;

    default:
        QWidget::keyPressEvent(pe);
    }
    updateGL();

}



GLuint OGLPyramid::createPyramid(GLfloat fSize) {
    GLuint n = glGenLists(1);

    glNewList(n, GL_COMPILE);
        glBegin(GL_TRIANGLE_FAN);
            qglColor(Qt::gray);
            glVertex3f(0.0, fSize, 0.0);
            glVertex3f(-fSize, -fSize, fSize);
            glVertex3f(fSize, -fSize, fSize);
            qglColor(Qt::darkBlue);
            glVertex3f(fSize, -fSize, -fSize);
            qglColor(Qt::darkMagenta);
            glVertex3f(-fSize, -fSize, -fSize);
            qglColor(Qt::white);
            glVertex3f(-fSize, -fSize, fSize);
        glEnd();

        glBegin(GL_QUADS);
            qglColor(Qt::red);
            glVertex3f(-fSize, -fSize, fSize);
            glVertex3f(fSize, -fSize, fSize);
            glVertex3f(fSize, -fSize, -fSize);
            glVertex3f(-fSize, -fSize, -fSize);
        glEnd();

        /*glBegin(GL_QUADS);
            qglColor(Qt::blue);
            glVertex3f(0, 2*fSize, 0);
            glVertex3f(fSize, 2*fSize, 0);
            glVertex3f(fSize, 2*fSize, fSize);
            glVertex3f(0, 2*fSize, fSize);
        glEnd();
        glBegin(GL_QUADS);
            qglColor(Qt::red);
            glVertex3f(0, 2*fSize, 0);
            glVertex3f(0, 2*fSize, fSize);
            glVertex3f(0, 3*fSize, fSize);
            glVertex3f(0, 3*fSize, 0);
        glEnd();*/
    glEndList();

    return n;
}
