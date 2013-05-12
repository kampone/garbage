#include "light.h"

const  GLfloat pi=3.141593, k=pi/180;
const GLuint np=36;
const GLfloat step=pi/np;
light::light(QWidget *parent) :
    QGLWidget(parent), m_xRotate(0), m_yRotate(0)
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
   genTextures(); // создать текстуры
   glEnable(GL_TEXTURE_2D); // установить режим двумерных текстур


   getVerTexArrays(); // определить массив текстурных координат вершин


   glEnableClientState(GL_TEXTURE_COORD_ARRAY); // активизация массива текстурных координат
}


void light::paintGL()
{
   glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

   glFlush();
   gluSphere(m_qObj,0.3f,100,100);

   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
   glTranslatef(0.0+m_xRotate, 0.0, 0.0);

   glRotatef(m_yRotate, 1.0, 0.0, 0.0);
   glRotatef(m_xRotate, 0.0, 1.0, 0.0);
}

/*void light::timerEvent(QTimerEvent *)
{

    m_xTimerRotate+=1;
    updateGL();
}*/

void light::getVerTexArrays() // определить массив вершин и массив текстурных координат
{
   GLfloat R=0.75f; // радиус сферы
   GLfloat phi, theta; // углы фи и тэта

   // двойной цикл по углам
   for (GLuint i=0; i < 2*np+1; i++)
   {
      phi=i*step; // изменение угла фи

      for (GLuint j=0; j < np+1; j++)
      {
         theta=j*step; // изменение угла тэта

         if (j==0) // вершины "северный полюс"
         {
            if (i<2*np)
            {
               vecVertices.push_back(0.0f); // пространственная x-координата вершины (добавить в конец вектора)
               vecVertices.push_back(0.0f); // пространственная y-координата вершины
               vecVertices.push_back(R);    // пространственная z-координата вершины

               vecTextures.push_back((phi+step/2)/(2*pi)); // текстурная x-координата вершины
               vecTextures.push_back(1.0f);                // текстурная y-координата вершины
            }
         }
         else
         {
            if (j<np) // вершины между северными и южными полюсами
            {
               if (i<2*np)
               {
                  vecVertices.push_back(R*sin(theta)*cos(phi));
                  vecVertices.push_back(R*sin(theta)*sin(phi));
                  vecVertices.push_back(R*cos(theta));

                  vecTextures.push_back(phi/(2*pi));
               }
               else
               {
                  vecVertices.push_back(R*sin(theta));
                  vecVertices.push_back(0.0f);
                  vecVertices.push_back(R*cos(theta));

                  vecTextures.push_back(1.0f);
               }
               vecTextures.push_back((pi-theta)/pi);
            }
            else // вершины "южный полюс"
            {
               if (i<2*np)
               {
                  vecVertices.push_back(0.0f);
                  vecVertices.push_back(0.0f);
                  vecVertices.push_back(-R);

                  vecTextures.push_back((phi+step/2)/(2*pi));
                  vecTextures.push_back(0.0f);
               }
            }
         }
      }
   }
}

void light::getIndexArray() // определить массив индексов
{
   for (GLuint i=0; i < 2*np; i++)
   {
      for (GLuint j=0; j < np; j++)
      {
         if (j==0)
         {
            vecIndices.push_back(i*(np+1));
            vecIndices.push_back(i*(np+1)+1);
            if (i<(2*np-1))
               vecIndices.push_back((i+1)*(np+1)+1);
            else
               vecIndices.push_back((i+1)*(np+1));
         }
         else
         {
            if (j<(np-1))
            {
               if (i<(2*np-1))
               {
                  vecIndices.push_back(i*(np+1)+j);
                  vecIndices.push_back((i+1)*(np+1)+(j+1));
                  vecIndices.push_back((i+1)*(np+1)+j);

                  vecIndices.push_back(i*(np+1)+j);
                  vecIndices.push_back(i*(np+1)+(j+1));
                  vecIndices.push_back((i+1)*(np+1)+(j+1));
               }
               else
               {
                  vecIndices.push_back(i*(np+1)+j);
                  vecIndices.push_back((i+1)*(np+1)+j);
                  vecIndices.push_back((i+1)*(np+1)+(j-1));

                  vecIndices.push_back(i*(np+1)+j);
                  vecIndices.push_back(i*(np+1)+(j+1));
                  vecIndices.push_back((i+1)*(np+1)+j);
               }
            }
            else
            {

               vecIndices.push_back((i+1)*(np+1)-1);
               if (i<(2*np-1))
                  vecIndices.push_back((i+2)*(np+1)-2);
               else
                  vecIndices.push_back((i+2)*(np+1)-3);
               vecIndices.push_back((i+1)*(np+1)-2);
            }
         }
      }
   }
}
void light::drawFigure() // построить фигуру
{
   // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // изобразить фигуру в виде каркаса
   //glColor4f(0.00f, 0.00f, 1.00f, 1.0f); // синий цвет

   glVertexPointer(3, GL_FLOAT, 0, vecVertices.begin()); // указываем, откуда нужно извлечь данные о массиве вершин
   glTexCoordPointer(2, GL_FLOAT, 0, vecTextures.begin()); // указываем, откуда нужно извлечь данные о массиве текстурных координат
   glDrawElements(GL_TRIANGLES, vecIndices.size(), GL_UNSIGNED_INT, vecIndices.begin()); // строим поверхности
    //glPointSize(3.0f); // размер точки примерно в пикселях

   // glDrawArrays(GL_POINTS, 0, vecVertices.size()/3); // изобразить массив в виде точек
}


//...

void light::genTextures() // функция genTexture() класса Scene3D, создаёт текстуры
{
   // загрузка изображений
  /* QImage image1; // создаём объекты класса QImage (изображения)

    image1.load("../textures/1.jpg"); // загружаем изображение в переменную image1

   image1=QGLWidget::convertToGLFormat(image1); // конвертируем изображение в формат для работы с OpenGL


   // создание имён для текстурных объектов
   glGenTextures(1, textureID); // создаём два имени и записываем их в массив

   // создаём и связываем текстурные объекты с состоянием текстуры
   // 1-ый текстурный объект
   glBindTexture(GL_TEXTURE_2D, textureID[1]); // создаём и связываем 1-ый текстурный объект с последующим состоянием текстуры
   glTexImage2D(GL_TEXTURE_2D, 0, 3, (GLsizei)image1.width(), (GLsizei)image1.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, image1.bits()); // связываем текстурный объект с изображением


   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); // задана линейная фильтрация вблизи
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); // задана линейная фильтрация вдали
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE); // при фильтрации игнорируются тексели, выходящие за границу текстуры для s координаты
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE); // при фильтрации игнорируются тексели, выходящие за границу текстуры для t координаты
   glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE); // цвет текселя полностью замещает цвет фрагмента фигуры
*/}
void light::mousePressEvent(QMouseEvent *pe) {
    m_ptPosition = pe->pos();
}

void light::mouseMoveEvent(QMouseEvent *pe) {
    m_yRotate += 180 * (GLfloat)(pe->y() - m_ptPosition.y()) / height();
    m_xRotate += 180 * (GLfloat)(pe->x() - m_ptPosition.x()) / width();
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
        m_yRotate-=1;
        break;
    case Qt::Key_S:
        m_yRotate+=1;
        break;
    case Qt::Key_A:
        m_xRotate-=1;
        break;
    case Qt::Key_D:
        m_xRotate+=1;
        break;
    default:
        QWidget::keyPressEvent(pe);
    }
updateGL();

}
