#include "scene3d.h"
#include <GL/glu.h>
#include <QApplication>
#include <QtOpenGL>
#include <QKeyEvent>

const static float pi=3.141593, k=pi/180;

GLfloat VertexArray[12][3];
GLfloat ColorArray[12][3];
GLubyte IndexArray[20][3];
Scene3D::Scene3D(QWidget *parent) :
    QGLWidget(parent)
{
    xRot=-90;
    yRot=0;
    zRot=0;
    zTra=0;
    nSca=1;
}

void Scene3D::initializeGL(){
    qglClearColor(Qt::white); // цвет для очистки буфера изображения - здесь просто фон окна
       glEnable(GL_DEPTH_TEST);  // устанавливает режим проверки глубины пикселей
       glShadeModel(GL_FLAT);    // отключает режим сглаживания цветов
       glEnable(GL_CULL_FACE);   // устанавливается режим, когда строятся только внешние поверхности

       getVertexArray(); // определить массив вершин
       getColorArray();  // определить массив цветов вершин
       getIndexArray();  // определить массив индексов вершин

       glEnableClientState(GL_VERTEX_ARRAY); // активизация массива вершин
       glEnableClientState(GL_COLOR_ARRAY);  // активизация массива цветов вершин
    }

void Scene3D::resizeGL(int w, int h){
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    GLfloat ratio=(GLfloat)w/(GLfloat)h;
    glOrtho(-1.0, 1.0, -1.0*ratio, 1.0*ratio, -10.0, 1.0);
    //glFrustum(-1.0,1.0,-1.0,1.0,1.0,10.0);
    glViewport(0,0,(GLint)w,(GLint)h);
}

void Scene3D::paintGL(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glScalef(nSca,nSca,nSca);
    glTranslatef(0.0f,zTra,0.0f);
    glRotatef(xRot,1.0f,0.0f,0.0f);
    glRotatef(yRot,0.0f,1.0f,0.0f);
    glRotatef(zRot,0.0f,0.0f,1.0f);

    drawAxis();
    drawFigure();
}

void Scene3D::mousePressEvent(QMouseEvent *pe){
    ptrMousePosition=pe->pos();

}

void Scene3D::mouseReleaseEvent(QMouseEvent *pe){

}

void Scene3D::mouseMoveEvent(QMouseEvent *pe){
    xRot += 180/nSca*(GLfloat)(pe->y()-ptrMousePosition.y())/height();
    zRot += 180/nSca*(GLfloat)(pe->x()-ptrMousePosition.x())/width();
    ptrMousePosition = pe->pos();

    updateGL();
}

void Scene3D::wheelEvent(QWheelEvent *pe){
    if((pe->delta())>0) scale_plus();
    else if((pe->delta())<0) scale_minus();

    updateGL();
}

void Scene3D::keyPressEvent(QKeyEvent *pe){
    switch (pe->key())
    {
    case Qt::Key_Plus:
        scale_plus();
    break;

    case Qt::Key_Equal:
        scale_plus();
    break;

    case Qt::Key_Minus:
        scale_minus();
    break;

    case Qt::Key_Up:
        rotate_up();
    break;

    case Qt::Key_Down:
        rotate_down();
    break;

    case Qt::Key_Left:
        rotate_left();
    break;

    case Qt::Key_Right:
        rotate_right();
    break;

    case Qt::Key_Z:
        translate_down();
    break;

    case Qt::Key_X:
        translate_up();
    break;

    case Qt::Key_Space:
        defaultScene();
    break;

    case Qt::Key_Escape:
        this->close();
    break;

    }
     updateGL();
}


void Scene3D::scale_plus(){
    nSca=nSca*1.1;
}

void Scene3D::scale_minus(){
    nSca=nSca/1.1;
}
void Scene3D::rotate_up(){
    xRot+=1.0;
}

void Scene3D::rotate_down(){
    xRot-=1.0;
}

void Scene3D::rotate_left(){
    zRot+=1.0;
}

void Scene3D::rotate_right(){
    zRot-=1.0;
}

void Scene3D::translate_down(){
    zTra-=0.05;
}

void Scene3D::translate_up(){
    zTra+=0.05;
}

void Scene3D::defaultScene() // наблюдение сцены по умолчанию
{
   xRot=-90; yRot=0; zRot=0; zTra=0; nSca=1;
}

void Scene3D::drawAxis() // построить оси координат
{
   glLineWidth(2.0f); // устанавливаю ширину линии приближённо в пикселях
   // до вызова команды ширина равна 1 пикселю по умолчанию

   glColor4f(1.00f, 0.00f, 0.00f, 1.0f); // устанавливается цвет последующих примитивов
   // ось x красного цвета
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

void Scene3D::getVertexArray() // определить массив вершин
{
   GLfloat R=0.75; // радиус сферы

   // начальные значения для икосаэдра
   GLfloat a=4*R/sqrt(10+2*sqrt(5)); // сторона икосаэдра
   GLfloat alpha=acos((1-a*a/2/R/R)); // первый угол поворота по тэта // cos(alpha)=(1-a*a/2/R/R)

   // вычисляем точки икосаэдра
   //0 точка
   VertexArray[0][0]=0;   // x
   VertexArray[0][1]=0;   // y
   VertexArray[0][2]=R;   // z

   //1 точка
   VertexArray[1][0]=R*sin(alpha)*sin(0);
   VertexArray[1][1]=R*sin(alpha)*cos(0);
   VertexArray[1][2]=R*cos(alpha);

   //2 точка
   VertexArray[2][0]=R*sin(alpha)*sin(72*k);
   VertexArray[2][1]=R*sin(alpha)*cos(72*k);
   VertexArray[2][2]=R*cos(alpha);

   //3 точка
   VertexArray[3][0]=R*sin(alpha)*sin(2*72*k);
   VertexArray[3][1]=R*sin(alpha)*cos(2*72*k);
   VertexArray[3][2]=R*cos(alpha);

   //4 точка
   VertexArray[4][0]=R*sin(alpha)*sin(3*72*k);
   VertexArray[4][1]=R*sin(alpha)*cos(3*72*k);
   VertexArray[4][2]=R*cos(alpha);

   //5 точка
   VertexArray[5][0]=R*sin(alpha)*sin(4*72*k);
   VertexArray[5][1]=R*sin(alpha)*cos(4*72*k);
   VertexArray[5][2]=R*cos(alpha);

   //6 точка
   VertexArray[6][0]=R*sin(pi-alpha)*sin(-36*k);
   VertexArray[6][1]=R*sin(pi-alpha)*cos(-36*k);
   VertexArray[6][2]=R*cos(pi-alpha);

   //7 точка
   VertexArray[7][0]=R*sin(pi-alpha)*sin(36*k);
   VertexArray[7][1]=R*sin(pi-alpha)*cos(36*k);
   VertexArray[7][2]=R*cos(pi-alpha);

   //8 точка
   VertexArray[8][0]=R*sin(pi-alpha)*sin((36+72)*k);
   VertexArray[8][1]=R*sin(pi-alpha)*cos((36+72)*k);
   VertexArray[8][2]=R*cos(pi-alpha);

   //9 точка
   VertexArray[9][0]=R*sin(pi-alpha)*sin((36+2*72)*k);
   VertexArray[9][1]=R*sin(pi-alpha)*cos((36+2*72)*k);
   VertexArray[9][2]=R*cos(pi-alpha);

   //10 точка
   VertexArray[10][0]=R*sin(pi-alpha)*sin((36+3*72)*k);
   VertexArray[10][1]=R*sin(pi-alpha)*cos((36+3*72)*k);
   VertexArray[10][2]=R*cos(pi-alpha);

   //11 точка
   VertexArray[11][0]=0;
   VertexArray[11][1]=0;
   VertexArray[11][2]=-R;
}

void Scene3D::getColorArray() // определить массив цветов вершин
{
   for (int i=0; i<12; i++)
   {
      ColorArray[i][0]=0.1f*(qrand()%11); // R - красная составляющая
      ColorArray[i][1]=0.1f*(qrand()%11); // G - зелёная составляющая
      ColorArray[i][2]=0.1f*(qrand()%11); // B - синяя составляющая
      // qrand()%11 - псевдослучайное число от 0 до 10
   }
}

void Scene3D::getIndexArray()   // определить массив индексов
{
   // 0 треугольник
   IndexArray[0][0]=0; // индекс (номер) 1-ой вершины
   IndexArray[0][1]=2; // индекс (номер) 2-ой вершины
   IndexArray[0][2]=1; // индекс (номер) 3-ей вершины

   // 1 треугольник
   IndexArray[1][0]=0;
   IndexArray[1][1]=3;
   IndexArray[1][2]=2;

   // 2 треугольник
   IndexArray[2][0]=0;
   IndexArray[2][1]=4;
   IndexArray[2][2]=3;

   // 3 треугольник
   IndexArray[3][0]=0;
   IndexArray[3][1]=5;
   IndexArray[3][2]=4;

   // 4 треугольник
   IndexArray[4][0]=0;
   IndexArray[4][1]=1;
   IndexArray[4][2]=5;

   // 5 треугольник
   IndexArray[5][0]=6;
   IndexArray[5][1]=1;
   IndexArray[5][2]=7;

   // 6 треугольник
   IndexArray[6][0]=7;
   IndexArray[6][1]=1;
   IndexArray[6][2]=2;

   // 7 треугольник
   IndexArray[7][0]=7;
   IndexArray[7][1]=2;
   IndexArray[7][2]=8;

   // 8 треугольник
   IndexArray[8][0]=8;
   IndexArray[8][1]=2;
   IndexArray[8][2]=3;

   // 9 треугольник
   IndexArray[9][0]=8;
   IndexArray[9][1]=3;
   IndexArray[9][2]=9;

   // 10 треугольник
   IndexArray[10][0]=9;
   IndexArray[10][1]=3;
   IndexArray[10][2]=4;

   // 11 треугольник
   IndexArray[11][0]=9;
   IndexArray[11][1]=4;
   IndexArray[11][2]=10;

   // 12 треугольник
   IndexArray[12][0]=10;
   IndexArray[12][1]=4;
   IndexArray[12][2]=5;

   // 13 треугольник
   IndexArray[13][0]=10;
   IndexArray[13][1]=5;
   IndexArray[13][2]=6;

   // 14 треугольник
   IndexArray[14][0]=6;
   IndexArray[14][1]=5;
   IndexArray[14][2]=1;

   // 15 треугольник
   IndexArray[15][0]=7;
   IndexArray[15][1]=11;
   IndexArray[15][2]=6;

   // 16 треугольник
   IndexArray[16][0]=8;
   IndexArray[16][1]=11;
   IndexArray[16][2]=7;

   // 17 треугольник
   IndexArray[17][0]=9;
   IndexArray[17][1]=11;
   IndexArray[17][2]=8;

   // 18 треугольник
   IndexArray[18][0]=10;
   IndexArray[18][1]=11;
   IndexArray[18][2]=9;

   // 19 треугольник
   IndexArray[19][0]=6;
   IndexArray[19][1]=11;
   IndexArray[19][2]=10;
}

void Scene3D::drawFigure() // построить фигуру
{
   glVertexPointer(3, GL_FLOAT, 0, VertexArray); // указываем, откуда нужно извлечь данные о массиве вершин
   glColorPointer(3, GL_FLOAT, 0, ColorArray);   // указываем, откуда нужно извлечь данные о массиве цветов вершин
   // используя массивы вершин и индексов,
   glDrawElements(GL_TRIANGLES, 60, GL_UNSIGNED_BYTE, IndexArray); // строим поверхности
}
