#include "vue_texte.h"
#include "Accelerateur.h"

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
	
	Collection_P collection;
	
	double x1(0.0);
	double y1(0.0);
	double z1(0.0);
	
	double x2(0.0);
	double y2(0.0);
	double z2(0.0);
	
	double dt(0.05);
	
	Faisceau f;
	
	for (size_t i=0; i<=50; ++i) {
		f.ajouter_par(p_Particule (new Particule(Vecteur3D(x1, y1, z1), Vecteur3D(x2, y2, z2), 2, 0.9834, -e)));
		x1+=dt; x2+=dt; y1+=dt; y2+=dt; z1+=dt; z2+=dt;
	}
	
	CERN.ajouter_faisceau(p_Faisceau (new Faisceau(f)));
	
	CERN.souder_accelerateur();
	CERN.initialiser_particules();
	
	p_Vue->dessine(f);
	
	CERN.affiche_part(cout);
	
	p_Vue->dessine(CERN);
 }
 catch (Erreur err) {cout << err.message;}
	
	return 0;
}
