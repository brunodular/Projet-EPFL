#include <QApplication>
#include "glwidget.h"
#include <iostream>
using namespace std;

int main(int argc, char* argv[])
{

  QApplication a(argc, argv);
  
    Accelerateur CERN(nullptr);
    
    GLWidget w(nullptr, &CERN);

  CERN.ajouter_el(new Quadrupole(Vecteur3D(3,2,0),Vecteur3D(3,1,0),0.3,1.2));
  CERN.ajouter_el(new SectionDroite(Vecteur3D(3,1,0),Vecteur3D(3,0,0),0.3));
  CERN.ajouter_el(new Quadrupole(Vecteur3D(3,0,0),Vecteur3D(3,-1,0),0.3,-1.2));
  CERN.ajouter_el(new SectionDroite(Vecteur3D(3,-1,0),Vecteur3D(3,-2,0),0.3));
  CERN.ajouter_el(new Dipole(Vecteur3D(3,-2,0),Vecteur3D(2,-3,0),0.3,1,5.89158));

  CERN.ajouter_el(new Quadrupole(Vecteur3D(2,-3,0),Vecteur3D(1,-3,0),0.3,1.2));
  CERN.ajouter_el(new SectionDroite(Vecteur3D(1,-3,0),Vecteur3D(0,-3,0),0.3));
  CERN.ajouter_el(new Quadrupole(Vecteur3D(0,-3,0),Vecteur3D(-1,-3,0),0.3,-1.2));
  CERN.ajouter_el(new SectionDroite(Vecteur3D(-1,-3,0),Vecteur3D(-2,-3,0),0.3));
  CERN.ajouter_el(new Dipole(Vecteur3D(-2,-3,0),Vecteur3D(-3,-2,0),0.3,1,5.89158));

  CERN.ajouter_el(new Quadrupole(Vecteur3D(-3,-2,0),Vecteur3D(-3,-1,0),0.3,1.2));
  CERN.ajouter_el(new SectionDroite(Vecteur3D(-3,-1,0),Vecteur3D(-3,0,0),0.3));
  CERN.ajouter_el(new Quadrupole(Vecteur3D(-3,0,0),Vecteur3D(-3,1,0),0.3,-1.2));
  CERN.ajouter_el(new SectionDroite(Vecteur3D(-3,1,0),Vecteur3D(-3,2,0),0.3));
  CERN.ajouter_el(new Dipole(Vecteur3D(-3,2,0),Vecteur3D(-2,3,0),0.3,1,5.89158));

  CERN.ajouter_el(new Quadrupole(Vecteur3D(-2,3,0),Vecteur3D(-1,3,0),0.3,1.2));
  CERN.ajouter_el(new SectionDroite(Vecteur3D(-1,3,0),Vecteur3D(0,3,0),0.3));
  CERN.ajouter_el(new Quadrupole(Vecteur3D(0,3,0),Vecteur3D(1,3,0),0.3,-1.2));
  CERN.ajouter_el(new SectionDroite(Vecteur3D(1,3,0),Vecteur3D(2,3,0),0.3));
  CERN.ajouter_el(new Dipole(Vecteur3D(2,3,0),Vecteur3D(3,2,0),0.3,1,5.89158));
    
    CERN.souder_accelerateur();
    
    Faisceau f(p_Particule (new Particule(Vecteur3D(3.01, 0, 0), Vecteur3D(0, -1, 0), 2, 0.938272, e)), 1000, 10, CERN);
    
    CERN.ajouter_faisceau(new Faisceau(f));
	
	CERN.initialiser_particules();
  
  w.show();
  
   return a.exec();
}
