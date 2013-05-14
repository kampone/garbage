#include "light.h"
#include <QGLWidget>

const  GLfloat pi=3.1415926535897932384626433832795, k=pi/180;
const GLuint np=36;
const GLfloat R=0.3f;
const GLfloat step=pi/np;
light::light(QWidget *parent) :
    QGLWidget(parent), m_xRotate(0), m_yRotate(0), m_xGo(0), m_yGo(0)
{

  m_qObj = gluNewQuadric();

}

void light::initializeGL()
{

   GLfloat mat_specular[]={1.0,1.0,1.0,1.0};
   GLfloat mat_shininess[]={50.0};
   GLfloat light_position[]={1.0,1.0,1.0,0.0};
   GLfloat white_light[]={1.0,1.0,1.0,1.0};

   glClearColor(0.0,0.0,0.0,0.0);
   glShadeModel(GL_FLAT);
   glMaterialfv(GL_FRONT,GL_SPECULAR,mat_specular);
   glMaterialfv(GL_FRONT,GL_SHININESS,mat_shininess);


   glLightfv(GL_LIGHT0,GL_POSITION,light_position);
   glLightfv(GL_LIGHT0,GL_DIFFUSE,white_light);
   glLightfv(GL_LIGHT0,GL_SPECULAR,white_light);

   glEnable(GL_LIGHTING);
   glEnable(GL_LIGHT0);
   glEnable(GL_DEPTH_TEST);

}

void light::paintGL()
{
   glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

   glFlush();
   gluSphere(m_qObj,R,20,20);

   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();

   glTranslatef(m_xGo, -m_yGo, 0.0);

   glRotatef(m_Rotate,m_yGo, m_xGo,0);
//glRotatef(m_yRotate, 0, 1.0f,0);
//glRotatef(m_yRotate, -m_yGo, m_xGo, 0.0f);



//drawAxis();
}
void light::drawAxis() // построить оси координат
{
   glLineWidth(5.0f); // устанавливаю ширину линии приближённо в пикселях
   // до вызова команды ширина равна 1 пикселю по умолчанию


   glBegin(GL_LINES); // построение линии
      glVertex3f( 1.0f,  0.0f,  0.0f); // первая точка
      glVertex3f(-1.0f,  0.0f,  0.0f); // вторая точка
   glEnd();

   QColor halfGreen(0, 128, 0, 255);
   qglColor(halfGreen);
   glBegin(GL_LINES);
      // ось y зеленого цвета
      glVertex3f( 0.0f,  1.0f,  0.0f);
      glVertex3f( 0.0f, -1.0f,  0.0f);

      glColor4f(0.00f, 0.00f, 1.00f, 1.0f);
      // ось z синего цвета
      glVertex3f( 0.0f,  0.0f,  1.0f);
      glVertex3f( 0.0f,  0.0f, -1.0f);
   glEnd();
}
void light::mousePressEvent(QMouseEvent *pe) {
    m_ptPosition = pe->pos();
}

void light::mouseMoveEvent(QMouseEvent *pe) {
   /* m_xRotate += 180 * (GLfloat)(pe->y() - m_ptPosition.y()) / height();
    m_yRotate += 180 * (GLfloat)(pe->x() - m_ptPosition.x()) / width();

    m_xGo=(m_yRotate*pi*R)/180;
    m_yGo=-(m_xRotate*pi*R)/180;
    */
    m_yGo+=2 * (GLfloat)(pe->y() - m_ptPosition.y()) / height();
    m_xGo+=2 * (GLfloat)(pe->x() - m_ptPosition.x()) / height();
    //m_yRotate=(m_xGo*180)/(pi*R);
    //m_xRotate=(m_yGo*180)/(pi*R);
    m_Rotate=(sqrt(m_yGo*m_yGo+m_xGo*m_xGo)*180.0)/(pi*R);
    updateGL();

    m_ptPosition = pe->pos();
}
void light::resizeGL(int w, int h)
{
   glViewport(0,0,(GLsizei) w, (GLsizei) h);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   //if (w<=h)
   //  glOrtho(-1.5,1.5,-0.5*(GLfloat)h/(GLfloat)w,0.5*(GLfloat)h/(GLfloat)w,-10.0,10.0);
   //else
      glOrtho(-1.5*(GLfloat)w/(GLfloat)h,1.5*(GLfloat)w/(GLfloat)h,-1.5,1.5,-10.0,10.0);
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
  /*  glViewport(0, 0, (GLint)w, (GLint)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    //GLfloat left=-0.2,right=0.2,bottom=-0.1125,top=0.1125,near=1.0,far=50.0;
    GLfloat left=-(GLint)w/2,right=(GLint)w,bottom=-(GLint)h,top=(GLint)h,near=1.0,far=50.0;
    //GLfloat left=-16.5,right=16.5,bottom=-10,top=10,near=50.0,far=4000.0;
    glFrustum(left, right, bottom, top, near, far);*/

}

void light::keyPressEvent(QKeyEvent *pe){

    switch(pe->key()){

    case Qt::Key_Escape:
        QApplication::exit();
        break;
    case Qt::Key_W:
        m_yGo-=0.03;

        break;
    case Qt::Key_S:
        m_yGo+=0.03;
        break;
    case Qt::Key_A:
        m_xGo-=0.03;
        break;
    case Qt::Key_D:
        m_xGo+=0.03;
        break;
    case Qt::Key_Space:
        defaultScene();
        break;
    default:
        QWidget::keyPressEvent(pe);
    }

    m_yRotate=(m_xGo*180)/(pi*R);
    m_xRotate=(m_yGo*180)/(pi*R);
    m_Rotate=(sqrt(m_yGo*m_yGo+m_xGo*m_xGo)*180.0)/(pi*R);
    updateGL();

}
void light::defaultScene() // наблюдение сцены по умолчанию
{
   m_xRotate=0;
   m_yRotate=0;
   m_xGo=0;
   m_yGo=0;
}


