#include "light.h"


light::light(QWidget *parent) :
    QGLWidget(parent)
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
   glShadeModel(GL_SMOOTH);
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
   gluSphere(m_qObj,1.0f,100,100);
   glFlush();
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
    //GLfloat left=-(GLint)nWidth/2,right=(GLint)nWidth,bottom=-(GLint)nHeight,top=(GLint)nHeight,near=1.0,far=50.0;
    GLfloat left=-16.5,right=16.5,bottom=-10,top=10,near=50.0,far=4000.0;
    glFrustum(left, right, bottom, top, near, far);*/
}

void light::keyPressEvent(QKeyEvent *pe){
    switch(pe->key()){
    /*case Qt::Key_W:
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


        break;*/
    case Qt::Key_Escape:
        QApplication::exit();
        break;

    default:
        QWidget::keyPressEvent(pe);
    }
    updateGL();

}

