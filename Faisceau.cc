#include "Faisceau.h"
#include <cmath>
using namespace std;

//=======================================================================

//Constructeur

Faisceau::Faisceau (p_Particule p, unsigned int nombre, const unsigned int lambda)
	: particule_typique(Particule* (new Particule (p))), lambda_(lambda)
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

unsigned int Faisceau::nombre_p() const {
	return lambda_*particules_.size();
}

//EVOLUTION

void evolue(double dt) {

}
