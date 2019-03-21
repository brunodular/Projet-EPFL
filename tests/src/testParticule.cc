#include <cmath>

#include "../../general/inc/Particule.h"
#include <iostream>
#include <iomanip>

using namespace std;

int main () {
cout.setf(ios::scientific);
cout << setprecision(10);

Particule p1(Vecteur3D (3.00984,-0.391837,0),Vecteur3D (-210200.0,-2.64754e+08,0), 2, 0.938272, e);
Particule p2(Vecteur3D (2.99016,-0.391837,0),Vecteur3D (210200.0,-2.64754e+08,0), 2, 0.938272, e);

cout << "P1 :" << endl << p1;
cout << "P2 :" << endl << p2;

Vecteur3D B(0,0,7); double dt(1e-11);
cout << "Ajout d'une force magnétique B = " << B << "(dt=" << dt << ")" << endl;
cout << " a P1:" << endl;
p1.ajouter_f_magn(B,dt);
cout << endl;
cout << " a P2: " << endl;
p2.ajouter_f_magn(B, dt);
cout << endl;

cout << "Les particules bougent une fois : " << endl;

p1.bouger(dt);
cout << "Nouveau P1 :" << endl << p1 << endl;

p2.bouger(dt);
cout << "Nouveau P2 : " << endl << p2 << endl;
/*

	cout << "Deux particules :" << endl << p1 << endl << " et " << p2 << endl;

	Vecteur3D B(0.0, 0.0, 7);
	const double dt (1e-11);

	cout << "Ajout d'une force magnetique B = " << B << "( dt = " << dt << " ) : " << endl;
	cout << "a p1 : " << endl;
  p1.ajouteForceMagnetique(B,dt);
  cout << p1 << endl;

	cout << "a p2 : " << endl;
  p2.ajouteForceMagnetique(B,dt);
  cout << p2 << endl;

	cout << "Les particules bougent une fois : ";

	p1.bouger(dt);
	p2.bouger(dt);

	cout << p1 << endl;

	cout << p2 <<endl;
*/
	return 0;

}
