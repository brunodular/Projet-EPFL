#pragma once
#include <iostream>
#include "Dessinable.h"
#include "Support_a_dessin.h"
#include "Particule.h"

//=======================================================================

//La classe Element est une classe abstraite dont héritent tous les différents types d'éléments.

class Element : public Dessinable {
protected:
  Vecteur3D pos_e_;   //position d'entrée
  Vecteur3D pos_s_;   //position de sortie
  const double r_section_;  //rayon de la section de la chambre à vide
  Vecteur3D dir_;     //direction de l'élément
  Element* el_suiv_ = nullptr;  //pointeur sur l'élément suivant
  Element* el_prec_ = nullptr;  //pointeur sur l'élément précédent
  double longueur_;

public:
  //Constructeur
  Element(Vecteur3D pos_e,Vecteur3D pos_s,double r_section,SupportADessin* support = nullptr);

  //Destructeur
  virtual ~Element() {};

  //Getters
  virtual Element* el_suiv() const;
  virtual Vecteur3D pos_e() const;
  virtual Vecteur3D pos_s() const;
  virtual double r_section() const;
  virtual double longueur() const;

  //Setters
  void el_suiv(Element*);
  void el_prec(Element*);

  //Méthodes
  virtual bool heurte_bord(Particule const& p) const = 0;

  bool passe_au_suivant(Particule& p) const;
  bool est_dans(Particule const& p) const;

  virtual Vecteur3D B(Particule const&) const; //champ magnétique

  virtual void affiche(std::ostream&) const;

  virtual double coord_orthogonale_position(Particule*) const = 0;
  virtual double coord_orthogonale_vitesse(Particule*) const = 0;

  virtual Vecteur3D abs_en_pos(double x) const = 0;
  virtual Abs pos_en_abs(p_Particule const&) const = 0;
  virtual Vecteur3D tangente_en_abs(double x, bool sens_horaire) const = 0;

  //DESSINER
  virtual void dessine() override { support_->dessine(*this); }
};

//=======================================================================

class ElementDroit : public Element {
public:
  //Constructeur
  ElementDroit(Vecteur3D pos_e,Vecteur3D pos_s,double r_section,SupportADessin* support = nullptr);

  //Destructeur
  virtual ~ElementDroit() {};

  //Méthodes
  virtual void affiche(std::ostream&) const override;

  virtual bool heurte_bord(Particule const& p) const override;

  virtual double coord_orthogonale_position(Particule*) const override;
  virtual double coord_orthogonale_vitesse(Particule*) const override;

  virtual Vecteur3D abs_en_pos(double x) const override;
  virtual Abs pos_en_abs(p_Particule const&) const override;
  virtual Vecteur3D tangente_en_abs(double x, bool sens_horaire) const override;

  //DESSINER
  virtual void dessine() override { support_->dessine(*this); }
};

//=======================================================================

class ElementCourbe : public Element {
protected:
  const double courbure_;
  const Vecteur3D centre_;

public:
  //Constructeur
  ElementCourbe(Vecteur3D pos_e,Vecteur3D pos_s,double r_section,double courbure,SupportADessin* support = nullptr);

  //Méthodes
  virtual Vecteur3D centre() const;

  virtual bool heurte_bord(Particule const&) const override;

  virtual void affiche(std::ostream&) const override;

  virtual double coord_orthogonale_position(Particule*) const override;
  virtual double coord_orthogonale_vitesse(Particule*) const override;

  virtual Vecteur3D abs_en_pos(double x) const override;
  virtual Abs pos_en_abs(p_Particule const&) const override;
  virtual Vecteur3D tangente_en_abs(double x, bool sens_horaire) const override;

  //DESSINER
  virtual void dessine() override { support_->dessine(*this); }
};

//=======================================================================

class SectionDroite : public ElementDroit {
public:
  //Constructeur
  SectionDroite(Vecteur3D pos_e,Vecteur3D pos_s,double r_section, SupportADessin* support = nullptr);

  //Méthodes
  virtual void affiche(std::ostream&) const override;

  //DESSINER
  virtual void dessine() override { support_->dessine(*this); }
};

//=======================================================================

class Dipole : public ElementCourbe {
private:
  const double Bz_; //intensité du champ magnétique vertical

public:
  //Constructeur
  Dipole(Vecteur3D pos_e,Vecteur3D pos_s,double r_section,double courbure,double Bz, SupportADessin* support = nullptr);

  //Méthodes
  virtual Vecteur3D B(Particule const&) const override;

  virtual void affiche(std::ostream&) const override;

  //DESSINER
  virtual void dessine() override { support_->dessine(*this); }
};

//=======================================================================

class Quadrupole : public ElementDroit {
private:
  const double b_; //intensité de l'aimant

public:
  //Constructeurs
  Quadrupole(Vecteur3D pos_e,Vecteur3D pos_s,double r_section,double b,SupportADessin* support = nullptr);

  virtual void affiche(std::ostream& sortie) const override;

  virtual Vecteur3D B(Particule const&) const override;

  //DESSINER
  virtual void dessine() override { support_->dessine(*this); }
};

class MailleFODO : public ElementDroit {
private:
  const double b_; //intensité des aimants des quadrupôles
  const double longueur_sect_; //longueurs des sections droites
  const double longueur_quad_; //longueurs des quadrupôles

public:
  MailleFODO(Vecteur3D pos_e,Vecteur3D pos_s,double r_section,double b,double l,SupportADessin* support = nullptr);

  double longueur_sect() const;
  double longueur_quad() const;
  Vecteur3D pos_e_sect_1() const;
  Vecteur3D pos_e_quad_2() const;
  Vecteur3D pos_e_sect_2() const;

  virtual void affiche(std::ostream& sortie) const override;
  virtual Vecteur3D B(Particule const&) const override;

  //DESSINER
  virtual void dessine() override {support_->dessine(*this);}
};
