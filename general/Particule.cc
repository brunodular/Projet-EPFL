#include "Particule.h"
#include "Accelerateur.h"
#include <cmath>
#include <iostream>
#include <iomanip>
using namespace std;

constexpr uint MARGE(25);

//========================================================================

//Constructeur
Particule::Particule(Vecteur3D pos, Vecteur3D v_dir, double E, Masse m, double q, SupportADessin* support)
 : Dessinable(support), pos_(pos), v_((c*sqrt(1-pow(m/E,2)))*(~v_dir)), m_(m), m_kg_(e*1e+9*m_/(c*c)), q_(q) {}

Particule::Particule(Accelerateur const& acc, double pos, Vecteur3D v_dir, double E, Masse m, double q, SupportADessin* support)
 : Particule(acc.abs_en_pos(pos),v_dir,E,m,q,support) {}

//=======================================================================

//getters

Vecteur3D Particule::pos() const {return pos_;}

Vecteur3D Particule::v() const {return v_;}

Vecteur3D Particule::F() const {return F_;}

double Particule::m() const {return m_;}

double Particule::q() const {return q_;}

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

//Etrange : la ligne de correction de la force fait une erreur de type char const*...
void Particule::ajouter_f_magn(Vecteur3D const& B,double dt) {
  if (!est_zero(dt) and !(est_zero(B.norme2()))) {
    //cout << "AJOUT DE LA FORCE MAGNETIQUE : " << endl;

    F_ += q_*(v_^B);
    //cout << F_ << endl;  //ICI
    //cout << "Angle : " << asin(dt*(F_.norme())/(2*gamma()*m_kg_*(v_.norme()))) << endl;
    F_ = F_.rotation((v_^F_),asin(dt*(F_.norme())/(2*gamma()*m_kg_*(v_.norme()))));
    //cout << F_ << endl; //ICI

  }
}

void Particule::bouger(double dt) {
  Vecteur3D a = (1/(gamma()*m_kg_))*F_;
  v_ = v_ + dt*a;
  pos_ += dt*v_;
  F_ = Vecteur3D();
}

bool Particule::est_sortie() {
  if (element_courant_ == nullptr or element_courant_->heurte_bord(*this)) {
    element_courant_ = nullptr;
    return true;
  } else return false;
}

ostream& Particule::affiche(ostream& out) const {
  return (out << "Une particule :" << endl << setw(MARGE) << "  position : " << pos_ << endl << setw(MARGE) << "  vitesse : " << v_ << endl << setw(MARGE) << "  gamma : " << gamma() << endl << setw(MARGE) << "  Energie (en GeV) : " << E() << endl << setw(MARGE) << "  Masse (en GeV/c^2) : " << m_ << endl << setw(MARGE) << "  Charge : " << q_ << endl << setw(MARGE) << "  Force : " << F_ << endl);
}

//=======================================================================

//Opérateurs externes
ostream& operator<<(ostream& out,Particule const& p) {
  return p.affiche(out);
}
