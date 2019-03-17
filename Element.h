#pragma once
#include <iostream>

#include "Particule.h"

//=======================================================================

class Element {
protected:
  const Vecteur3D pos_e_;   //position d'entrée
  const Vecteur3D pos_s_;   //position de sortie
  const double r_section_;  //rayon de la section de la chambre à vide
  const Vecteur3D dir_;     //direction de l'élément
  Element* el_suiv_;  //pointeur sur l'élément suivant

public:
  //Constructeur
  Element(Vecteur3D pos_e,Vecteur3D pos_s,double r_section,Element* el_suiv = nullptr);

  //Destructeur
  virtual ~Element() {};
	
  //Méthodes
  virtual bool heurte_bord(Particule const& p) const;

  virtual bool passe_au_suivant(Particule& p) const;

  virtual Vecteur3D B(Particule const&) const; //champ magnétique
  
  virtual void affiche(std::ostream&) const;
};

//=======================================================================

class ElementCourbe : public Element {
protected:
  const double courbure_;
  const Vecteur3D centre_;

public:
  //Constructeur
  virtual ElementCourbe(Vecteur3D pos_e,Vecteur3D pos_s,double r_section,double courbure,Element* el_suiv = nullptr);

  //Méthodes
  virtual bool heurte_bord(Particule const&) const override;
  
  virtual void affiche(std::ostream&) const override;
};

//=======================================================================

class SectionDroite : public Element {
public:
  //Constructeur
  SectionDroite(Vecteur3D pos_e,Vecteur3D pos_s,double r_section,Element* el_suiv = nullptr);
};

//=======================================================================

class Dipole : public ElementCourbe {
private:
  const double Bz_; //intensité du champ magnétique vertical

public:
  //Constructeur
  Dipole(Vecteur3D pos_e,Vecteur3D pos_s,double r_section,double courbure,double Bz,Element* el_suiv = nullptr);

  //Méthodes
  virtual Vecteur3D B(Particule const&) const override;
  
  virtual void affiche(std::ostream&) const override;
};
