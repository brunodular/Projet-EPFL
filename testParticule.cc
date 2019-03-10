#include "Particule.h"
#include <cmath>
#include <iostream>
using namespace std;

int main () {
	
	Particule p1(0.938272, 1.60217653e-19, Vecteur3D (3.00984, -0.391837, 0), 
		Vecteur3D (-210200, -2.64754e+08, 0), Vecteur3D (0.0, 0.0, 0.0), 2.13158, 2);
	Particule p2(0.938272, 1.60217653e-19, Vecteur3D (2.99016, -0.391837, 0), 
		Vecteur3D (-210200, -2.64754e+08, 0), Vecteur3D (0.0, 0.0, 0.0), 2.13158, 2);

	cout << "Deux particules :" << p1 << "  et " << p2;	
	
	Vecteur3D B (0.0, 0.0, 7);
	const double dt (1e-11);
	
	cout << " Ajoout d'une force magnetique B=" << B << "( dt = " <<dt 
	<< " ) : " <<endl;
	cout << "a P1 : "<<endl;
	
	cout << "a p2 : " << endl;
	
	cout << "Les particules bougent une fois : "
	
	p1.bouger();
	p2.bouger();
	
	cout << p1 << endl;
	
	cout <<p2<<endl;
	
	return 0;
	
}
