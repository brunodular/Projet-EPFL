#include "Faisceau.h"
#include <cmath>
using namespace std;

//=======================================================================

//Constructeur

Faisceau::Faisceau (Particule* p, unsigned int nb, unsigned int l)
	: particule_typique(Particule* (new Particule (p))), nb_p_(nb), lambda_(l) 
{}

//Methodes

void Faisceau::affiche(ostream& sortie) {
	sortie << "Particule typique du faisceau : " << endl;
	particule_typique_->affiche(sortie);
}

//GETTERS

double Faisceau::E_moyenne() const {
	return particule_typique_->E();
}


double Faisceau::emittance const {
	return sqrt();
}


double Faisceau::A_11() const {
	
}


double Faisceau::A_12() const {
	
}


double Faisceau::A_22() const {
	
}


