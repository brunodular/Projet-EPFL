#pragma once

#include <iostream>
#include "constantes.h"
#include "Vecteur3D.h"

class Element;

typedef const double Masse;

//=======================================================================

class Particule {
private:
  Vecteur3D pos_;
  Vecteur3D v_; //Vecteur directeur de la vitesse
  Masse m_; //en GeV/c^2
  Masse m_kg_; //en kg
  double q_;
  Vecteur3D F_;
  Element* element_courant_; //élément dans lequel se trouve la particule

public:
  //Constructeur
  Particule(Vecteur3D pos, Vecteur3D v_dir, double E, Masse m, double q, Vecteur3D F = Vecteur3D());

  //getters
  Vecteur3D pos() const;
  Element* element_courant() const;

  //setters
  void element_courant(Element* new_element);

  //Méthodes
  double E() const;
  double gamma() const;

  void ajouter_f_magn(Vecteur3D const&,double);

  void bouger(double);

  //Opérateurs
  std::ostream& affiche(std::ostream&) const;
};

//Opérateurs externes
std::ostream& operator<<(std::ostream&,Particule const&);
