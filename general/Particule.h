#pragma once

#include <iostream>
#include "Dessinable.h"
#include "Support_a_dessin.h"
#include "constantes.h"
#include "Vecteur3D.h"
#include "Element.h"

typedef const double Masse;

//=======================================================================

class Particule : public Dessinable {
private:
  Vecteur3D pos_;
  Vecteur3D v_; //Vecteur directeur de la vitesse
  Masse m_; //en GeV/c^2
  Masse m_kg_; //en kg
  double q_;
  Vecteur3D F_;	//Vecteur force
  Element* element_courant_; //élément dans lequel se trouve la particule

public:
  //Constructeur
  Particule(Vecteur3D pos, Vecteur3D v_dir, double E, Masse m, double q, SupportADessin* support = nullptr, Vecteur3D F = Vecteur3D());

  //getters
  Vecteur3D pos() const;
  Vecteur3D v() const;
  Element* element_courant() const;

  //setters
  void element_courant(Element* new_element);
  void setSupport(SupportADessin* support_) {support=support_;}
  
  //Méthodes
  double E() const;
  double gamma() const;

  void ajouter_f_magn(Vecteur3D const&,double);

  void bouger(double);

  bool est_sortie();

  //Opérateurs
  std::ostream& affiche(std::ostream&) const;

  //DESSINER
  virtual void dessine() override { support->dessine(*this); }
  
  //EVOLUTION
  
 void evolue (double) {}
};

//Opérateurs externes
std::ostream& operator<<(std::ostream&,Particule const&);
