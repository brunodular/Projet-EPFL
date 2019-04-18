#pragma once

#include <iostream>
#include "Dessinable.h"
#include "Support_a_dessin.h"
#include "constantes.h"
#include "Vecteur3D.h"
#include "Element.h"

class Case;

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
  Case* case_courante_; //case dans laquelle la particule se trouve

public:
  //Constructeur
  Particule(Vecteur3D pos, Vecteur3D v_dir, double E, Masse m, double q, SupportADessin* support = nullptr);
  Particule(Accelerateur const& acc, double pos, Vecteur3D v_dir, double E, Masse m, double q, SupportADessin* support = nullptr);
  
  //getters
  Vecteur3D pos() const;
  Vecteur3D v() const;
  Vecteur3D F() const;
  double m() const;
  double q() const;
  Element* element_courant() const;
  Case* case_courante() const;
  double E() const;
  double gamma() const;

  //setters
  void element_courant(Element* new_element);
  void case_courante(Case*);
  
  //Méthodes

  void ajouter_f_magn(Vecteur3D const&,double);
  void ajouter_force_inter_particulaire(Particule const&);

  void bouger(double);

  bool est_sortie();

  //Opérateurs
  std::ostream& affiche(std::ostream&) const;

  //DESSINER
  virtual void dessine() override { support_->dessine(*this); }
  
  //EVOLUTION
  
 void evolue (double) {}
};

//Opérateurs externes
std::ostream& operator<<(std::ostream&,Particule const&);
