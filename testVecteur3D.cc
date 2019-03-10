#include "Vecteur3D.h"
#include <iostream>
#include <cmath>
using namespace std;

int main () {
	Vecteur3D v(1.0, 2.0, -0.1);
	Vecteur3D w(2.6, 3.5, 4.1);
	Vecteur3D u(4.07, -5.96, 2.0);
	
//=======================================================================	
	
/* Premier test avec les methodes et sans surcharge d'operateurs	
 *
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
	*/
	
//=======================================================================	
	
//Tests avec surcharges d'operateurs
	Vecteur3D d;
	
	cout << "Vecteur1:" << v << endl;
	cout << "Vecteur2:" << w << endl;
	cout << "Vecteur3:" << u << endl;
	
	cout << "Comparaison:";
	if (w==v) { cout << "egal";}
	else {cout << "different";}
	cout << endl;
	
	cout << "Addition de v1 par v2: " << v+w << endl;
	
	cout << "Soustraction de v1 par v3:" << v-u << endl;
	
	cout << "Multiplication par 3:" << 3*v << endl;
	
	cout << "Produit scalaire de v1 par v2:" << v*w << endl;
	
	cout << "Produit vectoriel de v1 par v3: " << (v^u) << endl;
	
	cout << "Norme de v1:" << v.norme() << endl;
	
	cout << "Norme au carree de v3:" << u.norme2() << endl;
	
	cout << "Vecteur unitaire selon l'axe de v1: " << ~v << endl;	
	
	cout << "Produit mixte de v1 par v2 par v3: " << prod_mixte(v, w, u) << endl;
	
	cout << "Rotation de v1 selon l'axe de v2 par un angle de pi/6: "
	<< v.rotation(w, M_PI/6) << endl;
	
	return 0;
}
