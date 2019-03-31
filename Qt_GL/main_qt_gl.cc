#include <QApplication>
#include "glwidget.h"

int main(int argc, char* argv[])
{
  QApplication a(argc, argv);

  SupportADessin* p_Vue(new VueOpenGL());
  
  Accelerateur CERN(p_Vue);
  
  CERN.ajouter_el(new Quadrupole(Vecteur3D(3,2,0),Vecteur3D(3,1,0),0.1,1.2));
  
  Faisceau f;
  f.ajouter_par(p_Particule (new Particule(Vecteur3D(1.00984, -0.191837, 0), Vecteur3D(-210200, -2.64754e+08, 0), 2, 0.938272, e)));
  CERN.ajouter_faisceau(p_Faisceau (new Faisceau(f)));
  
  GLWidget w(nullptr, &CERN);

  w.show();

  return a.exec();
}
