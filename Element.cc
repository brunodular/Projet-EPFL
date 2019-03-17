#include <cmath>
using namespace std;

//=======================================================================

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
virtual bool Element::heurte_bord(Particule const& p) const {
  Vecteur3D X(p.pos()-pos_e_);
  return (X-(X*dir_)*dir_).norme2() > r_section_*r_section_;
}

virtual bool Element::passe_au_suivant(Particule& p) const {
  if (prod_mixte(e3,p.pos(),pos_s_) > 0) {
    p.element_courant(el_suiv_);
    return true;
  } else {
    return false;
  }
}

virtual Vecteur3D Element::B(Particule const&) const {
  return Vecteur3D();
}

virtual void Element::affiche(ostream& sortie) const {
	sortie << "  entree : " << pos_e_ << endl << "  sortie : " << pos_s_ << endl << "  rayon de chambre : " << r_section_ << endl;
}

//=======================================================================

//Class ElementCourbe

//Constructeurs
ElementCourbe::ElementCourbe(Vecteur3D pos_e,Vecteur3D pos_s,double r_section,double courbure,Element* el_suiv) :
  Element(pos_e, pos_s, r_section, el_suiv),
  courbure_(courbure),
  centre_(0.5*(pos_e_+pos_s_)+(1/k)*sqrt(1-k*k*0.25*(pos_s_-pos_e_).norme2())*(dir_^e3)) {}

//Méthodes
virtual bool ElementCourbe::heurte_bord(Particule const& p) const {
  Vecteur3D X(p.pos()-pos_e_);
  return (X-(1/abs(k))*(~(X-X.z()*e3))).norme2() > r_section_*r_section_;
}

virtual void ElementCourbe::affiche(ostream& sortie) const {
	this->Element::affiche(sortie);
	sortie<<"  rayon de courbure : " << courbure_ << endl;
}

//=======================================================================

//Class SectionDroite
SectionDroie::SectionDroite(Vecteur3D pos_e,Vecteur3D pos_s,double r_section,Element* el_suiv) : Element(pos_e, pos_s, r_section, el_suiv) {}

//=======================================================================

//Class Dipole

//Constructeurs

Dipole::Dipole(Vecteur3D pos_e,Vecteur3D pos_s,double r_section,double courbure,double Bz,Element* el_suiv) :
  Element(pos_e, pos_s, r_section, courbure, el_suiv),
  Bz_(Bz) {}

//Méthodes
virtual Vecteur3D Dipole::B(Particule const&) const {
  return Vecteur3D(0,0,Bz_);
}

virtual void affiche(ostream& sortie) const {
	this->ElementCourbe::affiche(sortie);
	sortie << "  champ magnetique : " << Vecteur3D(0, 0, Bz_) << endl;
}
