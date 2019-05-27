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
  Vecteur3D pos_; //position
  Vecteur3D v_; //Vecteur directeur de la vitesse
  Masse m_; //en GeV/c^2
  Masse m_kg_; //en kg
  double q_; //charge
  Vecteur3D F_;	//Vecteur force
  Element* element_courant_ = nullptr; //élément dans lequel se trouve la particule
  size_t case_courante_ = 0;			//indice de la "case_courante" de la particule dans le vector d'ensemble de pointeurs vers des particules, cases_, de l'accelerateur sur lequel on lance la simulation

public:
  //Constructeurs
  Particule(Vecteur3D pos, Vecteur3D v_dir, double E, Masse m, double q, SupportADessin* support = nullptr);	//Constructeur "classique" de Particule

  Particule(Accelerateur const& acc, double pos, bool sens_horaire, double E, Masse m, double q, SupportADessin* support = nullptr); //Constructeur de Particule utilise pour mettre le vecteur vitesse de la particule dans le sens de la trajectoire ideale de l'accelerateur et de direction le sens-horaire (ou pas selon le booleen)

  Particule(Accelerateur const& acc, double pos_longi, double pos_vert, double pos_transv, bool sens_horaire, double E, Masse m, double q, SupportADessin* support = nullptr);

  //On ne definit pas de destructeur car le destructeur par defaut suffit

  //getters
  Vecteur3D pos() const;
  Vecteur3D v() const;
  Vecteur3D F() const;
  double m() const;
  double q() const;
  Element* element_courant() const;
  double E() const;		//retourne l'energie
  double gamma() const;	//retourne le coefficient gamma
  size_t case_courante() const;

  //setters
  void element_courant(Element* new_element);
  void case_courante(size_t i);

  //Méthodes
		//Forces
  void supprimer_forces();
  void ajouter_force_inter_particulaire(Particule const&);
  void ajouter_f_magn(Vecteur3D const&,double);

		//Evolution
  void bouger(double);

		//AUTRES
  bool est_sortie();

  //Opérateurs
  std::ostream& affiche(std::ostream&) const;

  //DESSINER
  virtual void dessine() override { support_->dessine(*this); }
};

//Opérateurs externes
std::ostream& operator<<(std::ostream&,Particule const&);
