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
  Element* el_preced_; //pointeur sur l'élément précédent afin de pouvoir faire tourner des particules dans l'autre sens dans l'accélérateur
  Element* el_suiv_;  //pointeur sur l'élément suivant
  double longueur_;

public:
  //Constructeur
  Element(Vecteur3D pos_e,Vecteur3D pos_s,double r_section,SupportADessin* support = nullptr,Element* el_suiv = nullptr);

  //Destructeur
  virtual ~Element() {};

  //Getters
  //virtual Element* el_suiv() const;
  virtual Vecteur3D pos_e() const;
  virtual Vecteur3D pos_s() const;
  virtual double r_section() const;
  virtual double longueur() const;
  
  //Setters
  virtual void el_suiv(Element*);
  virtual void el_preced(Element*);

  //Méthodes
  virtual bool heurte_bord(Particule const& p) const = 0;

  virtual bool passe_au_suivant(Particule& p) const;

  virtual Vecteur3D B(Particule const&) const; //champ magnétique
	
	//Affiche
  virtual void affiche(std::ostream&) const;

	//Coordonees orthogonales
  virtual double coord_orthogonale_position(Particule*) const = 0;
  virtual double coord_orthogonale_vitesse(Particule*) const = 0;
  
	//Abscisse curviligne
  virtual Vecteur3D abs_en_pos(double x) const = 0;
  virtual Abs pos_en_abs(Particule const&) const = 0;

  //DESSINER
  virtual void dessine() override { support_->dessine(*this); }
};

//=======================================================================

class ElementDroit : public Element {
public:
  //Constructeur
  ElementDroit(Vecteur3D pos_e,Vecteur3D pos_s,double r_section,SupportADessin* support = nullptr,Element* el_suiv = nullptr);

  //Destructeur
  virtual ~ElementDroit() {};

  //Méthodes
  virtual void affiche(std::ostream&) const override;

  virtual bool heurte_bord(Particule const& p) const override;

  virtual double coord_orthogonale_position(Particule*) const override;
  virtual double coord_orthogonale_vitesse(Particule*) const override;
  
  virtual Vecteur3D abs_en_pos(double x) const override;
  virtual Abs pos_en_abs(Particule const&) const override;

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
  ElementCourbe(Vecteur3D pos_e,Vecteur3D pos_s,double r_section,double courbure,SupportADessin* support = nullptr,Element* el_suiv = nullptr);

  //Méthodes
  virtual Vecteur3D centre() const;
  
  virtual bool heurte_bord(Particule const&) const override;

  virtual void affiche(std::ostream&) const override;

  virtual double coord_orthogonale_position(Particule*) const override;
  virtual double coord_orthogonale_vitesse(Particule*) const override;
  
  virtual Vecteur3D abs_en_pos(double x) const override;
  virtual Abs pos_en_abs(Particule const&) const override;

  //DESSINER
  virtual void dessine() override { support_->dessine(*this); }
};

//=======================================================================

class SectionDroite : public ElementDroit {
public:
  //Constructeur
  SectionDroite(Vecteur3D pos_e,Vecteur3D pos_s,double r_section, SupportADessin* support = nullptr, Element* el_suiv = nullptr);

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
  Dipole(Vecteur3D pos_e,Vecteur3D pos_s,double r_section,double courbure,double Bz, SupportADessin* support = nullptr, Element* el_suiv = nullptr);

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
  Quadrupole(Vecteur3D pos_e,Vecteur3D pos_s,double r_section,double b,SupportADessin* support = nullptr,Element* el_suiv = nullptr);

  virtual void affiche(std::ostream& sortie) const override;

  virtual Vecteur3D B(Particule const&) const override;

  //DESSINER
  virtual void dessine() override { support_->dessine(*this); }
};
