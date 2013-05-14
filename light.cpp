#include "light.h"
#include <QGLWidget>
#include <QDebug>

const  GLdouble pi=3.1415926535897932384626433832795, k=pi/180;
const GLuint np=36;
const GLfloat R=0.3f;
const GLfloat step=pi/np;

void multM(const GLdouble *matrix, GLdouble *vector)
{
   //qDebug()<<matrix[0]<<" "<<matrix[1]<<" "<<matrix[2]<<" "<<matrix[3];
   //qDebug()<<matrix[4]<<" "<<matrix[5]<<" "<<matrix[6]<<" "<<matrix[7];
   //qDebug()<<matrix[8]<<" "<<matrix[9]<<" "<<matrix[10]<<" "<<matrix[11];
   //qDebug()<<matrix[12]<<" "<<matrix[13]<<" "<<matrix[14]<<" "<<matrix[15];
   GLdouble result[4]={0.0, 0.0, 0.0, 0.0};
   for(int i=0; i<4; ++i)
      for(int k=0; k<4; ++k){
         result[i]+=matrix[i+4*k]*vector[k];
         //qDebug()<<"result["<<i<<"] "<<result[i];
      }
   for(int i=0; i<4; ++i){
      vector[i]=result[i];
      //qDebug()<<"vector["<<i<<"] "<<vector[i];
   }
}

light::light(QWidget *parent) :
    QGLWidget(parent),
    //m_xRotate(0),
    //m_yRotate(0),
    m_xGo(0.0),
    m_yGo(0.0),
    m_Phi(0.0),
    m_dx(0.0),
    m_dy(0.0),
    m_dPhi(0.0)
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
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();

}

void light::paintGL()
{
   glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

   //glFlush();


   glMatrixMode(GL_MODELVIEW);
   //glLoadIdentity();
   qDebug()<<"m_xGo: "<<m_dx;
   qDebug()<<"m_yGo: "<<m_dy;
   qDebug()<<"m_Phi: "<<m_dPhi;
   //m_xGo+=m_dx;
   //m_yGo+=m_dy;
   //m_Phi+=m_dPhi;

   //GLdouble theta=0.0;
   GLdouble matrix[16];
   glGetDoublev(GL_MODELVIEW_MATRIX,matrix);
   GLdouble point[4]={0.0, 0.0, 0.0, 1.0}, vector[4]={0.0, 0.0, 1.0, 0.0};
   multM(matrix,point);
   m_xGo=point[0];
   m_yGo=point[1];
   GLdouble z=point[2];
   qDebug()<<"0point  ("<<point[0]<<", "<<point[1]<<", "<<point[2]<<")";

   qDebug()<<matrix[0]<<" "<<matrix[4]<<" "<<matrix[8]<<" "<<matrix[12];
   qDebug()<<matrix[1]<<" "<<matrix[5]<<" "<<matrix[9]<<" "<<matrix[13];
   qDebug()<<matrix[2]<<" "<<matrix[6]<<" "<<matrix[10]<<" "<<matrix[14];
   qDebug()<<matrix[3]<<" "<<matrix[7]<<" "<<matrix[11]<<" "<<matrix[15];

   glTranslated(-m_xGo, -m_yGo, -z);
   point[0]=0.0;
   point[1]=0.0;
   point[2]=0.0;
   point[3]=1.0;
   glGetDoublev(GL_MODELVIEW_MATRIX,matrix);
   qDebug()<<"matrix1";
   qDebug()<<matrix[0]<<" "<<matrix[4]<<" "<<matrix[8]<<" "<<matrix[12];
   qDebug()<<matrix[1]<<" "<<matrix[5]<<" "<<matrix[9]<<" "<<matrix[13];
   qDebug()<<matrix[2]<<" "<<matrix[6]<<" "<<matrix[10]<<" "<<matrix[14];
   qDebug()<<matrix[3]<<" "<<matrix[7]<<" "<<matrix[11]<<" "<<matrix[15];
   multM(matrix,point);
   qDebug()<<"1point  ("<<point[0]<<", "<<point[1]<<", "<<point[2]<<")";

   glRotated(m_dPhi,m_dy, -m_dx,0.0);
   point[0]=0.0;
   point[1]=0.0;
   point[2]=0.0;
   point[3]=1.0;
   glGetDoublev(GL_MODELVIEW_MATRIX,matrix);
   qDebug()<<"matrixR";
   qDebug()<<matrix[0]<<" "<<matrix[4]<<" "<<matrix[8]<<" "<<matrix[12];
   qDebug()<<matrix[1]<<" "<<matrix[5]<<" "<<matrix[9]<<" "<<matrix[13];
   qDebug()<<matrix[2]<<" "<<matrix[6]<<" "<<matrix[10]<<" "<<matrix[14];
   qDebug()<<matrix[3]<<" "<<matrix[7]<<" "<<matrix[11]<<" "<<matrix[15];
   multM(matrix,point);
   qDebug()<<"Rpoint  ("<<point[0]<<", "<<point[1]<<", "<<point[2]<<")";
   glTranslated(m_xGo, m_yGo, z);
   point[0]=0.0;
   point[1]=0.0;
   point[2]=0.0;
   point[3]=1.0;
   glGetDoublev(GL_MODELVIEW_MATRIX,matrix);
   qDebug()<<"matrix2";
   qDebug()<<matrix[0]<<" "<<matrix[4]<<" "<<matrix[8]<<" "<<matrix[12];
   qDebug()<<matrix[1]<<" "<<matrix[5]<<" "<<matrix[9]<<" "<<matrix[13];
   qDebug()<<matrix[2]<<" "<<matrix[6]<<" "<<matrix[10]<<" "<<matrix[14];
   qDebug()<<matrix[3]<<" "<<matrix[7]<<" "<<matrix[11]<<" "<<matrix[15];
   multM(matrix,point);
   qDebug()<<"2point  ("<<point[0]<<", "<<point[1]<<", "<<point[2]<<")";
   glTranslated(m_dx, m_dy, 0.0);

   point[0]=0.0;
   point[1]=0.0;
   point[2]=0.0;
   point[3]=1.0;
   glGetDoublev(GL_MODELVIEW_MATRIX,matrix);
   qDebug()<<"matrix3";
   qDebug()<<matrix[0]<<" "<<matrix[4]<<" "<<matrix[8]<<" "<<matrix[12];
   qDebug()<<matrix[1]<<" "<<matrix[5]<<" "<<matrix[9]<<" "<<matrix[13];
   qDebug()<<matrix[2]<<" "<<matrix[6]<<" "<<matrix[10]<<" "<<matrix[14];
   qDebug()<<matrix[3]<<" "<<matrix[7]<<" "<<matrix[11]<<" "<<matrix[15];
   multM(matrix,point);
   qDebug()<<"3point  ("<<point[0]<<", "<<point[1]<<", "<<point[2]<<")";
   multM(matrix,vector);
   qDebug()<<"vector ("<<vector[0]<<", "<<vector[1]<<", "<<vector[2]<<")";

   gluSphere(m_qObj,R,20,20);
   drawAxis();
   glFlush();

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
    m_dy=-2 * (GLfloat)(pe->y() - m_ptPosition.y()) / height();
    m_dx=2 * (GLfloat)(pe->x() - m_ptPosition.x()) / width();
    //m_yGo+=dx;
    //m_xGo+=dy;
    //m_yRotate=(m_xGo*180)/(pi*R);
    //m_xRotate=(m_yGo*180)/(pi*R);
    m_dPhi=(sqrt(m_dy*m_dy+m_dx*m_dx)*180.0)/(pi*R);
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
        m_dy=+0.03;
        m_dx=0.0;
        break;
    case Qt::Key_S:
        m_dy=-0.03;
        m_dx=0.0;
        break;
    case Qt::Key_A:
        m_dx=-0.03;
        m_dy=0.0;
        break;
    case Qt::Key_D:
        m_dx=+0.03;
        m_dy=0.0;
        break;
    case Qt::Key_Space:
        defaultScene();
        break;
    default:
        QWidget::keyPressEvent(pe);
    }

    //m_yRotate=(m_xGo*180)/(pi*R);
    //m_xRotate=(m_yGo*180)/(pi*R);
    m_dPhi=(0.03*180.0)/(pi*R);
    updateGL();

}
void light::defaultScene() // наблюдение сцены по умолчанию
{
   //m_xRotate=0;
   //m_yRotate=0;
   //m_xGo=0;
   //m_yGo=0;
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
}


