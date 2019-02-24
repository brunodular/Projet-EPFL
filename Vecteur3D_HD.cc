#include <iostream>
#include <cmath>
#include "Vecteur3D_HD.h"

//--------------------------------------------------------------

/*Fonction d'affichage utilisee dans les tests*/

void Vecteur3D::affiche() const {
	cout.setf(ios::showpoint);
	std::cout << x << " " << y << " " << z << std::endl;
};


bool Vecteur3D::compare(Vecteur3D v) const  {
	return (v.x==x) and (v.y==y) and (v.z==z);
};

//---------------------------------------------------------------

/* Methodes de la classe Vecteur3D: Definitions des methodes qui seront 
 * utiles lors de calcul physique au cours de la modelisation: */
 
 
Vecteur3D Vecteur3D::addition(Vecteur3D const& v) const {
	Vecteur3D c(v.x+x, v.y+y, v.z+z);
	return c;
};


Vecteur3D Vecteur3D::soustraction(Vecteur3D const& v) const {
	return addition(v.oppose());
};


Vecteur3D Vecteur3D::oppose() const {
	Vecteur3D c(-x, -y, -z);
	return c;
};


Vecteur3D Vecteur3D::mult(double const& a) const {
	Vecteur3D c(a*x, a*y, a*z);
	return c;
};


double Vecteur3D::prod_scal(Vecteur3D const& v) const {
	return v.x*x+v.y*y+v.z*z;
};


Vecteur3D Vecteur3D::prod_vect(Vecteur3D const& v) const {
	Vecteur3D c(y*v.z-z*v.y, z*v.x-x*v.z, x*v.y-y*v.x);
	return c;
};


double Vecteur3D::norme() const {
	return sqrt(x*x+y*y+z*z);
};


double Vecteur3D::norme2() const {
	return x*x+y*y+z*z;
};


Vecteur3D Vecteur3D::unitaire() const {
	Vecteur3D c(x/(sqrt(x*x+y*y+z*z)), y/(sqrt(x*x+y*y+z*z)), z/(sqrt(x*x+y*y+z*z)));
	return c;
};

//---------------------------------------------------------------

/*Fonctions:*/

double prod_mixte(Vecteur3D const& u, Vecteur3D const& v, Vecteur3D const& w) {
	return u.prod_scal(v.prod_vect(w));
};
