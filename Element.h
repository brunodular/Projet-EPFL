#pragma once
#include <iostream>
#include "Dessinable.h"
#include "Support_a_dessin.h"
#include "Particule.h"

//=======================================================================

class Element : public Dessinable {
protected:
  Vecteur3D pos_e_;   //position d'entrée
  Vecteur3D pos_s_;   //position de sortie
  const double r_section_;  //rayon de la section de la chambre à vide
  Vecteur3D dir_;     //direction de l'élément
  Element* el_suiv_;  //pointeur sur l'élément suivant

public:
  //Constructeur
  Element(Vecteur3D pos_e,Vecteur3D pos_s,double r_section,SupportADessin* support,Element* el_suiv = nullptr);

  //Destructeur
  virtual ~Element() {};
	
  //Méthodes
  virtual bool heurte_bord(Particule const& p) const;

  virtual bool passe_au_suivant(Particule& p) const;

  virtual Vecteur3D B(Particule const&) const; //champ magnétique
  
  virtual void affiche(std::ostream&) const;
  
  //DESSINER
  virtual void dessine() override { support->dessine(*this); }
};

//=======================================================================

class ElementCourbe : public Element {
protected:
  const double courbure_;
  const Vecteur3D centre_;

public:
  //Constructeur
  ElementCourbe(Vecteur3D pos_e,Vecteur3D pos_s,double r_section,double courbure,SupportADessin* support,Element* el_suiv = nullptr);

  //Méthodes
  virtual bool heurte_bord(Particule const&) const override;
  
  virtual void affiche(std::ostream&) const override;
  
  //DESSINER
  virtual void dessine() override { support->dessine(*this); }
};

//=======================================================================

class SectionDroite : public Element {
public:
  //Constructeur
  SectionDroite(Vecteur3D pos_e,Vecteur3D pos_s,double r_section, SupportADessin* support, Element* el_suiv = nullptr);
  
  //DESSINER
  virtual void dessine() override { support->dessine(*this); }
};

//=======================================================================

class Dipole : public ElementCourbe {
private:
  const double Bz_; //intensité du champ magnétique vertical

public:
  //Constructeur
  Dipole(Vecteur3D pos_e,Vecteur3D pos_s,double r_section,double courbure,double Bz, SupportADessin* support, Element* el_suiv = nullptr);

  //Méthodes
  virtual Vecteur3D B(Particule const&) const override;
  
  virtual void affiche(std::ostream&) const override;
  
  //DESSINER
  virtual void dessine() override { support->dessine(*this); }
};
