#include <QApplication>
#include "glwidget.h"

int main(int argc, char* argv[])
{
  //Ce test n'est plus adapte au code et nous ne l'avons pas mis a jour

  QApplication a(argc, argv);

  VueOpenGL Vue;

  Particule p(Vecteur3D(1.00984, -0.191837, 0), Vecteur3D(-210200, -2.64754e+08, 0), 2, 0.938272, e);

  GLWidget w(nullptr, &p);

  w.show();

  return a.exec();
}
