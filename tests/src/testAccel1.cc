#include "../../texte/inc/Vue_Texte.h"
#include "../../dessin/inc/Support_a_dessin.h"
#include <iostream>
using namespace std;

int main() {
try {

	SupportADessin* p_Vue(new Vue_Texte(cout));


	Accelerateur acc1(p_Vue);

  //C'est plus logique de créer les éléments, particules en les intégrant à l'accélérateur, plutôt que de les créer et puis d'en mettre une copie dans l'accélérateur après. J'ai donc modifié la suite.

  //acc1.ajouter_el(new Dipole(Vecteur3D(1, 0, 0), Vecteur3D(0, -1, 0), 0.1, 1, 7, p_Vue));

  //acc1.ajouter_el(new SectionDroite(Vecteur3D(0, 5, 0), Vecteur3D (7, 0, 0), 0.4, p_Vue));

  acc1.ajouter_el(new Quadrupole(Vecteur3D(0,-1,0),Vecteur3D(1,0,0),0.2,3,p_Vue));

	acc1.ajouter_par(new Particule(Vecteur3D(1.00984, -0.191837, 0), Vecteur3D(-210200, -2.64754e+08, 0), 2, 0.938272, e, p_Vue));

	acc1.ajouter_par(new Particule(Vecteur3D(0.99016, -0.191837, 0), Vecteur3D(210200, -2.64754e+08, 0), 2, 0.938272, e, p_Vue));

	cout << "Accelerateur 1 : " << endl;
	p_Vue->dessine(acc1);
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
