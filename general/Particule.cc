#include "Particule.h"
#include "Accelerateur.h"
#include <cmath>
#include <iostream>
#include <iomanip>
using namespace std;

//========================================================================

//Constructeur
Particule::Particule(Vecteur3D pos, Vecteur3D v_dir, double E, Masse m, double q, SupportADessin* support)
 : Dessinable(support), pos_(pos), v_((c*sqrt(1-pow(m/E,2)))*(~v_dir)), m_(m), m_kg_(e*1e+9*m_/(c*c)), q_(q) {}

Particule::Particule(Accelerateur const& acc, double pos, bool sens_horaire, double E, Masse m, double q, SupportADessin* support)
 : Particule(acc.abs_en_pos(pos), acc.tangente_en_abs(pos, sens_horaire),E,m,q,support) {}

Particule::Particule(Accelerateur const& acc, double pos_longi, double pos_vert, double pos_transv, bool sens_horaire, double E, Masse m, double q, SupportADessin* support)
  : Particule(acc.abs_en_pos(pos_longi, pos_transv, pos_vert), acc.tangente_en_abs(pos_longi, sens_horaire),E,m,q,support) {}

//=======================================================================

//getters

Vecteur3D Particule::pos() const {return pos_;}

Vecteur3D Particule::v() const {return v_;}

Vecteur3D Particule::F() const {return F_;}

double Particule::m() const {return m_;}

double Particule::q() const {return q_;}

Element* Particule::element_courant() const {return element_courant_;}

size_t Particule::case_courante() const {return case_courante_;}

//setters

void Particule::element_courant(Element* new_element) {element_courant_ = new_element;}

void Particule::case_courante(size_t i) {case_courante_ = i;}

//=======================================================================

//Méthodes

double Particule::E() const {
  return gamma()*m_kg_*c*c*(1e-9)/e;
}

double Particule::gamma() const {
  return 1/sqrt(1-(v_.norme2()/(c*c)));		//pas besoin de mettre des exceptions car la vitesse ne peut pas depasse la vitesse de la lumiere
}

void Particule::ajouter_f_magn(Vecteur3D const& B,double dt) {
  if (!est_zero(dt) and !(est_zero(B.norme2()))) {
    F_ += q_*(v_^B);
    F_ = F_.rotation((v_^F_),asin(dt*(F_.norme())/(2*gamma()*m_kg_*(v_.norme()))));
  }
}

void Particule::ajouter_force_inter_particulaire(Particule const& p) {

  Vecteur3D r(p.pos()-pos_);
	double d=r.norme();
	if (!est_zero(d*d*d)) {
		double g=gamma();
		double F = (q_*p.q()/(4*M_PI*e_0*d*d*d*g*g)); //force a ajouter
    if (F == F) { //verifie si F est un NaN (not a number), car les NaN ont la particularite que toute expression logique qui en contient est false.
      F_ += F*r;
    }
	}

}

void Particule::supprimer_forces() {
  F_ = Vecteur3D();
}

void Particule::bouger(double dt) {
  v_ += dt*((1/(gamma()*m_kg_))*F_);
  pos_ += dt*v_;
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
