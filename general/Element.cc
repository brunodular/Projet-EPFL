#include <cmath>
#include "Element.h"
#include <string>
#include <iomanip>
using namespace std;

//=======================================================================

//Class Element

//Constructeurs
Element::Element(Vecteur3D pos_e,Vecteur3D pos_s,double r_section,SupportADessin* support)
 : Dessinable(support), r_section_(r_section), longueur_(0.0) {
    double prod(prod_mixte(e3,pos_e,pos_s));
    if (prod == 0) { //pour s'assurer que l'élément est dans le bon sens
      Erreur err = {"position d'entrée = position de sortie",2};
      throw err;
    } else if (prod > 0) {
      pos_s_ = pos_e; pos_e_ = pos_s;
    } else {
      pos_s_ = pos_s; pos_e_ = pos_e;
    }
    dir_ = ~(pos_s_-pos_e_);
  }

//Getters
Element* Element::el_suiv() const {
  return el_suiv_;
}
Vecteur3D Element::pos_e() const {
  return pos_e_;
}
Vecteur3D Element::pos_s() const {
  return pos_s_;
}
double Element::r_section() const {
  return r_section_;
}
double Element::longueur() const {
  return longueur_;
}

//Setters
void Element::el_suiv(Element* el) {
  el_suiv_ = el;
}

void Element::el_prec(Element* el) {
  el_prec_ = el;
}

//Méthodes
bool Element::passe_au_suivant(Particule& p) const {
  if (p.v() * dir_ > 0) {
    if (prod_mixte(e3,p.pos(),pos_s_) > 0) {
      p.element_courant(el_suiv_);
      return true;
    } else {
      return false;
    }
  } else {
    if (prod_mixte(e3,p.pos(),pos_e_) < 0) {
      p.element_courant(el_prec_);
      return true;
    } else {
      return false;
    }
  }
}

bool Element::est_dans(Particule const& p) const {
  if (prod_mixte(e3,p.pos(),pos_s_) < 0 and prod_mixte(e3,p.pos(),pos_e_) > 0) {
    if (not heurte_bord(p)) return true;
    else return false;
  } else return false;
}

Vecteur3D Element::B(Particule const&) const {
  return Vecteur3D();
}

void Element::affiche(ostream& sortie) const {
	sortie << setw(MARGE) << "  entree : " << pos_e_ << endl << setw(MARGE) << "  sortie : " << pos_s_ << endl << setw(MARGE) << "  rayon de chambre : " << r_section_ << endl;
}

//=======================================================================

//Class ElementDroit

//Constructeur
ElementDroit::ElementDroit(Vecteur3D pos_e,Vecteur3D pos_s,double r_section,SupportADessin* support) :
  Element(pos_e, pos_s, r_section, support) {
    longueur_ = (pos_s_ - pos_e_).norme();
  }

//Méthodes
void ElementDroit::affiche(ostream& sortie) const {
  Element::affiche(sortie);
}

double ElementDroit::coord_orthogonale_position(Particule* p) const {
  return p->pos() * (e3^dir_);
}
double ElementDroit::coord_orthogonale_vitesse(Particule* p) const {
  return p->v() * (e3^dir_);
}

bool ElementDroit::heurte_bord(Particule const& p) const {
  Vecteur3D X(p.pos()-pos_e_);
  return (X-(X*dir_)*dir_).norme2() > r_section_*r_section_;
}

Vecteur3D ElementDroit::abs_en_pos(double x) const {
  return pos_e_ + (x*longueur_)*dir_;
}

Abs ElementDroit::pos_en_abs(p_Particule const& p) const {
	return (p->pos()-pos_e_)*dir_;
}


//=======================================================================

//Class ElementCourbe

//Constructeurs
ElementCourbe::ElementCourbe(Vecteur3D pos_e,Vecteur3D pos_s,double r_section,double courbure,SupportADessin* support) :
  Element(pos_e, pos_s, r_section, support),
  courbure_(courbure),
  centre_(0.5*(pos_e_+pos_s_)+(1/courbure_)*sqrt(1-courbure_*courbure_*0.25*(pos_s_-pos_e_).norme2())*(dir_^e3)) {
    longueur_ = 2*asin((pos_s_ - pos_e_).norme()*courbure_/2.0)/courbure_;
  }

//Méthodes
Vecteur3D ElementCourbe::centre() const {
  return centre_;
}

bool ElementCourbe::heurte_bord(Particule const& p) const {
  Vecteur3D X(p.pos()-centre_);
  return (X-(1/abs(courbure_))*(~(X-X.z()*e3))).norme2() > r_section_*r_section_;
}

void ElementCourbe::affiche(ostream& sortie) const {
	Element::affiche(sortie);
	sortie<< setw(MARGE) <<"  rayon de courbure : " << courbure_ << endl;
}

double ElementCourbe::coord_orthogonale_position(Particule* p) const {
  return p->pos() * (~(p->pos() - (p->pos().z())*e3));
}
double ElementCourbe::coord_orthogonale_vitesse(Particule* p) const {
  return p->v() * (~(p->pos() - (p->pos().z()*e3)));
}

Vecteur3D ElementCourbe::abs_en_pos(double x) const {
  double theta(2*asin(longueur_*courbure_/2)); //angle au centre de courbure
  Vecteur3D u(pos_s_-centre_);
  Vecteur3D v(u^e3);
  return centre_ + cos(x*theta)*u+sin(x*theta)*v;
}

Abs ElementCourbe::pos_en_abs(p_Particule const& p) const {
	Vecteur3D x=p->pos()-(e3*p->pos())*e3;
	return acos((pos_e_*x)*courbure_/x.norme())/courbure_;
}

//=======================================================================

//Class SectionDroite

SectionDroite::SectionDroite(Vecteur3D pos_e,Vecteur3D pos_s,double r_section,SupportADessin* support)
: ElementDroit(pos_e, pos_s, r_section, support) {}

//Méthodes
void SectionDroite::affiche(ostream& sortie) const {
  sortie << "Section droite" << endl;
  ElementDroit::affiche(sortie);
}

//=======================================================================

//Class Dipole

//Constructeurs

Dipole::Dipole(Vecteur3D pos_e,Vecteur3D pos_s,double r_section,double courbure,double Bz,SupportADessin* support) :
  ElementCourbe(pos_e, pos_s, r_section, courbure, support), Bz_(Bz) {}

//Méthodes
Vecteur3D Dipole::B(Particule const& p) const {
  return Vecteur3D(0,0,Bz_);
}

void Dipole::affiche(ostream& sortie) const {

	sortie << "Dipole" << endl;
	ElementCourbe::affiche(sortie);
	sortie << setw(MARGE) << "  champ magnetique : " << Vecteur3D(0, 0, Bz_) << endl;
}

//=======================================================================

//Class Quadrupole

//Constructeurs
Quadrupole::Quadrupole(Vecteur3D pos_e,Vecteur3D pos_s,double r_section,double b,SupportADessin* support) : ElementDroit(pos_e,pos_s,r_section,support), b_(b) {}

//Méthodes
void Quadrupole::affiche(std::ostream& sortie) const {
  sortie << "Quadrupôle" << endl;
  ElementDroit::affiche(sortie);
  sortie << setw(MARGE) << "  intensité de l'aimant : " << b_ << endl;
}

Vecteur3D Quadrupole::B(Particule const& p) const {
  Vecteur3D X(p.pos() - pos_e_);
  Vecteur3D Y(X-(X*dir_)*dir_); //calcul des coordonnées locales
  return b_*((Y*(e3^dir_))*e3 + (X.z() * (e3^dir_))); //calcul du champ magnétique
}

//=======================================================================

//Class MailleFODO

MailleFODO::MailleFODO(Vecteur3D pos_e,Vecteur3D pos_s,double r_section,double b,double l,SupportADessin* support) : ElementDroit(pos_e,pos_s,r_section,support), b_(b), longueur_quad_(l), longueur_sect_(0.5*longueur_-l) {}

double MailleFODO::longueur_sect() const {return longueur_sect_;}
double MailleFODO::longueur_quad() const {return longueur_quad_;}
Vecteur3D MailleFODO::pos_e_sect_1() const {return pos_e_ + longueur_quad_*dir_;}
Vecteur3D MailleFODO::pos_e_quad_2() const {return pos_e_ + (longueur_quad_+longueur_sect_)*dir_;}
Vecteur3D MailleFODO::pos_e_sect_2() const {return pos_e_ + (2*longueur_quad_+longueur_sect_)*dir_;}

void MailleFODO::affiche(std::ostream& sortie) const {
  sortie << "Maille FODO" << endl;
  ElementDroit::affiche(sortie);
  sortie << setw(MARGE) << "  longueur des quadrupôles : " << longueur_quad_ << endl;
  sortie << setw(MARGE) << "  intensité des aimants : " << b_ << endl;
}

Vecteur3D MailleFODO::B(Particule const& p) const {
  Vecteur3D X(p.pos() - pos_e_);
  double abscisse(X*dir_);
  if (abscisse < longueur_quad_) {
    Vecteur3D Y(X-(X*dir_)*dir_); //calcul des coordonnées locales au premier quadrupôle
    return b_*((Y*(e3^dir_))*e3 + (X.z() * (e3^dir_))); //calcul du champ magnétique
  } else if (abscisse > longueur_quad_ + longueur_sect_ and abscisse < longueur_ - longueur_sect_) {
    X = p.pos() - (pos_e_+dir_*(0.5*longueur_));
    Vecteur3D Y(X-(X*dir_)*dir_); //calcul des coordonnées locales au second quadrupôle
    return -b_*((Y*(e3^dir_))*e3 + (X.z() * (e3^dir_))); //calcul du champ magnétique
  } else return Vecteur3D();
}
