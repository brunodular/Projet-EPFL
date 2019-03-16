#pragma once

#include <iostream>
#include "constantes.h"
#include "Vecteur3D.h"

typedef const double Masse;

class Particule {
private:
  Vecteur3D pos_;
  Vecteur3D v_; //Vecteur directeur de la vitesse
  Masse m_; //en GeV/c^2
  Masse m_kg_; //en kg
  double q_;
  Vecteur3D F_;

public:
  //Constructeur
  Particule(Vecteur3D pos, Vecteur3D v_dir, double E, Masse m, double q, Vecteur3D F = Vecteur3D());

  //getters
  Vecteur3D pos() const;

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
