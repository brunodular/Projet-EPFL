#include <QApplication>
#include "glwidget.h"

int main(int argc, char* argv[])
{
  QApplication a(argc, argv);

  Accelerateur CERN;
  GLWidget w(nullptr, &CERN);

  CERN.ajouter_el(new Quadrupole(Vecteur3D(3,2,0),Vecteur3D(3,1,0),0.1,1.2));
  CERN.ajouter_el(new SectionDroite(Vecteur3D(3,1,0),Vecteur3D(3,0,0),0.1));
  CERN.ajouter_el(new Quadrupole(Vecteur3D(3,0,0),Vecteur3D(3,-1,0),0.1,-1.2));
  CERN.ajouter_el(new SectionDroite(Vecteur3D(3,-1,0),Vecteur3D(3,-2,0),0.1));
  CERN.ajouter_el(new Dipole(Vecteur3D(3,-2,0),Vecteur3D(2,-3,0),0.1,1,5.89158));

  CERN.ajouter_el(new Quadrupole(Vecteur3D(2,-3,0),Vecteur3D(1,-3,0),0.1,1.2));
  CERN.ajouter_el(new SectionDroite(Vecteur3D(1,-3,0),Vecteur3D(0,-3,0),0.1));
  CERN.ajouter_el(new Quadrupole(Vecteur3D(0,-3,0),Vecteur3D(-1,-3,0),0.1,-1.2));
  CERN.ajouter_el(new SectionDroite(Vecteur3D(-1,-3,0),Vecteur3D(-2,-3,0),0.1));
  CERN.ajouter_el(new Dipole(Vecteur3D(-2,-3,0),Vecteur3D(-3,-2,0),0.1,1,5.89158));

  CERN.ajouter_el(new Quadrupole(Vecteur3D(-3,-2,0),Vecteur3D(-3,-1,0),0.1,1.2));
  CERN.ajouter_el(new SectionDroite(Vecteur3D(-3,-1,0),Vecteur3D(-3,0,0),0.1));
  CERN.ajouter_el(new Quadrupole(Vecteur3D(-3,0,0),Vecteur3D(-3,1,0),0.1,-1.2));
  CERN.ajouter_el(new SectionDroite(Vecteur3D(-3,1,0),Vecteur3D(-3,2,0),0.1));
  CERN.ajouter_el(new Dipole(Vecteur3D(-3,2,0),Vecteur3D(-2,3,0),0.1,1,5.89158));

  CERN.ajouter_el(new Quadrupole(Vecteur3D(-2,3,0),Vecteur3D(-1,3,0),0.1,1.2));
  CERN.ajouter_el(new SectionDroite(Vecteur3D(-1,3,0),Vecteur3D(0,3,0),0.1));
  CERN.ajouter_el(new Quadrupole(Vecteur3D(0,3,0),Vecteur3D(1,3,0),0.1,-1.2));
  CERN.ajouter_el(new SectionDroite(Vecteur3D(1,3,0),Vecteur3D(2,3,0),0.1));
  CERN.ajouter_el(new Dipole(Vecteur3D(2,3,0),Vecteur3D(3,2,0),0.1,1,5.89158));

  CERN.souder_accelerateur();

  w.show();

  return a.exec();
}
