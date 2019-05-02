#include "Accelerateur.h"
#include "vue_texte.h"
using namespace std;

int main() {
  try {
    Vue_Texte* p_Vue (new Vue_Texte(cout));
    Accelerateur CERN(p_Vue);

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

    CERN.initialiser_particules();

    CERN.dessine();
    //CERN.affiche_part(cout);

    for (double i(0); i<2; i += 0.05) {
      cout << i << " : " << CERN.abs_en_pos(i) << endl;
    }
  } catch (char const* error) {cerr << *error << endl;}

  return 0;
}
