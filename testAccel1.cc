#include "Accelerateur.h"
#include "Vue_Texte.h"
using namespace std;


int main() {
	
	Vue_Texte Vue(cout);
	SupportADessin* p_Vue(new Vue_Texte(cout));
	Dipole d(Vecteur3D(1, 0, 0), Vecteur3D(0, -1, 0), 0.1, 1, 7, p_Vue);
	try {ElementCourbe el(Vecteur3D(0, 5, 6), Vecteur3D (7, 0, 0), 0.4, 3, p_Vue);
	Particule p1(Vecteur3D(1.00984, -0.191837, 0), Vecteur3D(-210200, -2.64754e+08, 0), 2, 0.938272, e, p_Vue);
	Particule p2(Vecteur3D(0.99016, -0.191837, 0), Vecteur3D(210200, -2.64754e+08, 0), 2, 0.938272, e, p_Vue);
	Particule p3(Vecteur3D (2.99016,-0.391837,0),Vecteur3D (210200.0,-2.64754e+08,0), 2, 0.938272, e, p_Vue);
	p_Particule p1_(new Particule(p1));
	p_Particule p2_(new Particule(p2));
	p_Element d_(new Dipole(d));
	
	Accelerateur acc1;
	acc1.ajouter_el(d_);
	acc1.ajouter_par(p1_);
	acc1.ajouter_par(p2_);
	
	Accelerateur acc2(Collection_P {p1_}, Collection_E{d_}, p_Vue);
	
	cout << "Accelerateur 2 : " << endl;
	
	Vue.dessine(acc2);
	/*
	cout << "Accelerateur 1 : " << endl;
	
	cout << acc1 << endl;
	
	cout << "Ajout d'un element a l'accelerateur 1 : " << endl;
	
	p_Element el_(new ElementCourbe (el));
	acc1.ajouter_el(el_);
	
	cout << acc1 << endl;
	
	cout << "Ajout d'une particule a l'accelerateur 1 : " << endl;
	
	p_Particule p3_(new Particule (p3));
	acc1.ajouter_par(p3_);
	
	cout << acc1 << endl;
	
	cout << "Supprimer tous les elements de l'accelerateur 1 : " << endl;
	
	acc1.supprimer_el();
	
	cout << acc1 << endl;
	
	cout << "Supprimer toutes les particules de l'accelerateur 1 : " << endl;
	
	acc1.supprimer_par();
	
	cout << acc1 << endl;*/
	}
	catch (Erreur err) {cout << err.message;}
	
	return 0;
}
