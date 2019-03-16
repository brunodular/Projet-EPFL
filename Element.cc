#include "Element.h"
#include <cmath>

//Class Element

//Constructeurs
Element::Element(Vecteur3D pos_e,Vecteur3D pos_s,double r_section,Element* el_suiv) :
  r_section_(r_section),
  el_suiv_(el_suiv) {
    double prod(prod_mixte(e3,pos_e,pos_s));
    if (prod = 0) { //pour s'assurer que l'élément est dans le bon sens
      Erreur err = {"position d'entrée = position de sortie",2}
      throw err;
    } else if (prod > 0) {
      pos_s_ = pos_e; pos_e_ = pos_s;
    } else {
      pos_s_ = pos_s; pos_e_ = pos_e;
    }
    dir_ = ~(pos_s_-pos_e_);
  }

//Méthodes
bool Element::heurte_bord(Particule const& p) const {
  Vecteur3D X(p.pos()-pos_e_);
  return (X-(X*dir_)*dir_).norme2() > r_section_*r_section_;
}

bool Element::passe_au_suivant(Particule const&) const {
  return prod_mixte(e3,p.pos(),pos_s_) > 0;
}


//Class ElementCourbe

//Constructeurs
ElementCourbe::ElementCourbe(Vecteur3D pos_e,Vecteur3D pos_s,double r_section,double courbure,Element* el_suiv) :
  Element(pos_e, pos_s, r_section, el_suiv),
  courbure_(courbure),
  centre_(0.5*(pos_e_+pos_s_)+(1/k)*sqrt(1-k*k*0.25*(pos_s_-pos_e_).norme2())*(dir_^e3)) {}

//Méthodes
bool ElementCourbe::heurte_bord(Particule const& p) const {
  Vecteur3D X(p.pos()-pos_e_);
  return (X-(1/abs(k))*(~(X-X.z()*e3))).norme2() > r_section_*r_section_;
}


//Class SectionDroite
SectionDroie::SectionDroite(Vecteur3D pos_e,Vecteur3D pos_s,double r_section,Element* el_suiv) : Element(pos_e, pos_s, r_section, el_suiv) {}


//Class Dipole

//Constructeurs

Dipole::Dipole(Vecteur3D pos_e,Vecteur3D pos_s,double r_section,double courbure,double Bz,Element* el_suiv) :
  Element(pos_e, pos_s, r_section, courbure, el_suiv),
  Bz_(Bz) {}
