
#include <QApplication>
#include "OGLQuad.h"
#include "OGLPyramid.h"
#include "light.h"
#include "scene3d.h"

/*int main (int argc, char** argv) {
    QApplication app (argc, argv);
    OGLQuad oglQuad;
    OGLPyramid oglPyramid;

   // oglQuad.resize(500, 500);
    //oglQuad.show();
    //oglQuad.showFullScreen();

    oglPyramid.resize(500, 500);
    oglPyramid.showFullScreen();

    return app.exec();
}
*/
int main(int argc, char **argv)
{
    QApplication app (argc, argv);
    Scene3D w;

    w.resize(500,500);
    w.showFullScreen();


   return app.exec();
}
