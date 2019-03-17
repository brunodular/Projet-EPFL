#include "Particule.h"
#include <cmath>
#include <iostream>
using namespace std;

//========================================================================

//Constructeur
Particule::Particule(Vecteur3D pos, Vecteur3D v_dir, double E, Masse m, double q, Vecteur3D F)
 : pos_(pos), v_((c*sqrt(1-pow(m/E,2)))*(~v_dir)), m_(m), m_kg_(e*1e+9*m_/(c*c)), q_(q), F_(F) {}

//=======================================================================

//getters

Vecteur3D Particule::pos() const {return pos_;}

Element* Particule::element_courant() const {return element_courant_;}

//setters

void Particule::element_courant(Element* new_element) {element_courant_ = new_element;}

//=======================================================================

//Méthodes

double Particule::E() const {
  return gamma()*m_kg_*c*c*(1e-9)/e;
}

double Particule::gamma() const {
  return 1/sqrt(1-(v_.norme2()/(c*c)));
}

void Particule::ajouter_f_magn(Vecteur3D const& B,double dt) {
  if (!est_zero(dt)) {
    F_ += q_*(v_^B);
    cout << F_ << endl;  //ICI
    cout << "Angle : " << asin(dt*(F_.norme())/(2*gamma()*m_kg_*(v_.norme()))) << endl;
    F_ = F_.rotation((v_^F_),asin(dt*(F_.norme())/(2*gamma()*m_kg_*(v_.norme()))));
    cout << F_ << endl; //ICI
     
  }
}

void Particule::bouger(double dt) {
  Vecteur3D a = (1/(gamma()*m_kg_))*F_;
  v_ = v_ + dt*a;
  pos_ += dt*v_;
  F_ = Vecteur3D();
}


ostream& Particule::affiche(ostream& out) const {
  return (out << "Une particule :" << endl << "  position : " << pos_ << endl << "  vitesse : " << v_ << endl << "  gamma : " << gamma() << endl << "  Energie (en GeV) : " << E() << endl << "  Masse (en GeV/c^2) : " << m_ << endl << "  Charge : " << q_ << endl << "  Force : " << F_ << endl);
}

//=======================================================================

//Opérateurs externes
ostream& operator<<(ostream& out,Particule const& p) {
  return p.affiche(out);
}
