#include "Particule.h"
#include <iostream>
#include <cmath>
using namespace std;

//=======================================================================

//METHODES

void Particule::E() {
	E_=gamma_*M_*pow(c,2);
}

void Particule::v() {
	v_=(*this).quantite_mvt()*(1/(sqrt(pow(M_, 2)+pow(((*this).quantite_mvt().norme()/c),2))));
}

void Particule::gamma() {
	gamma_=1/(sqrt(1-pow((v_.norme()/c),2)));
}

void Particule::ajouteForceMagnetique(Vecteur3D const& B, double dt) {
	if (dt!=0) {
		force_+=Q_*(v_^B);
		force_=force_.rotation((v_^force_), asin(dt*force_.norme()/(2*gamma_*M_*v_.norme())));
	}
}
	
Vecteur3D Particule::quantite_mvt() {
	return gamma_*M_*v_.norme();
}

void Particule::bouger(double dt) {
	Vecteur3D a=1/(gamma_*M_)*force_;
	v_=v_+dt*a;
	pos_=pos_+dt*v_;
	force_=Vecteur3D (0.0, 0.0, 0.0);
}
		
ostream& Particule::afficher(ostream& sortie) const {
	sortie<<"Une particule : "<<endl;
	sortie<< "  position : " << pos_ << endl;
	sortie<< "  vitesse : " << v_ << endl;
	sortie<< "  gamma : " << gamma_ << endl;
	sortie<< "  energie (GeV) : " << E_ << endl;
	sortie<< "  masse (GeV/c^2) : " << M_;
	sortie<< "  charge : " << Q_ << endl;
	sortie<< "  force : " << force_;
	return sortie;
}

//=======================================================================

//OPERATEURS

//Operateur externe

ostream& operator<<(ostream& sortie, Particule const& x) {
	return x.afficher(sortie);
}
