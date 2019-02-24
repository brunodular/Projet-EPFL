#include "Vecteur3D.h"
#include <iostream>
using namespace std;
cout.setf(ios::showpoint);

int main () {
	Vecteur3D v(1.0, 2.0, -0.1);
	Vecteur3D w(2.6, 3.5, 4.1);
	
	cout << "Vecteur1:"; v.affiche();
	cout << "Vecteur2:"; w.affiche();
	
	cout << "Comparaison:";
	if (w.compare(v)) { cout << "egal";}
	else {cout << "different";}
	cout << endl;
	
	cout << "Addition de v1 par v2: ";
	(v.addition(w)).affiche();
	cout << endl;
	
	cout << "Soustraction de v1 par v2:";
	(v.soustraction(w)).affiche();
	cout << endl;
	
	cout << "Multiplication par 3:";
	(v.mult(3)).affiche();
	cout << endl;
	
	cout << "Produit scalaire de v1 par v2:";
	cout << v.prod_scal(w)<< endl;
	
	cout << "Produit vectoriel de v1 par v2: ";
	(v.prod_vect(w)).affiche();
	cout << endl;
	
	cout << "Norme de v1:";
	cout << v.norme() << endl;
	
	cout << "Norme au carree de v1:";
	cout << v.norme2() << endl;
	
	cout << "Vecteur unitaire selon l'axe de v1: ";
	(v.unitaire()).affiche();
	cout << endl;
	
	
	return 0;
}
