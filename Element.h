#pragma once

#include "Particule.h"

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

  //Méthodes
  bool heurte_bord(Particule const&) const;

  bool passe_au_suivant(Particule const&) const;
};

class ElementCourbe : public Element {
protected:
  const double courbure_;
  const Vecteur3D centre_;

public:
  //Constructeur
  ElementCourbe(Vecteur3D pos_e,Vecteur3D pos_s,double r_section,double courbure,Element* el_suiv = nullptr);

  //Méthodes
  bool heurte_bord(Particule const&) const;
};

class SectionDroite : public Element {
public:
  SectionDroite(Vecteur3D pos_e,Vecteur3D pos_s,double r_section,Element* el_suiv = nullptr);

};

class Dipole : public ElementCourbe {
private:
  const double Bz_; //intensité du champ magnétique vertical

public:
  Dipole(Vecteur3D pos_e,Vecteur3D pos_s,double r_section,double courbure,double Bz,Element* el_suiv = nullptr);
};
