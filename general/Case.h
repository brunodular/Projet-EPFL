#pragma once

#include "Particule.h"
#include "Dessinable.h"
#include <vector>
#include <iostream>

class Accelerateur;

typedef std::vector<Particule*> Collection_P;
typedef double Abs; //Nombre entre 0 et 1 qui représente l'abscisse curviligne

class Case : public Dessinable {
	private:
		Collection_P particules_;
		Vecteur3D pos_e_;
		Vecteur3D pos_s_;
		Case* case_suiv_;
		Case* case_preced_;
	
	public:
		
		//Constructeur
		Case (Abs, Abs, Accelerateur const&);
		Case(Case const&)= delete;
		Case& operator=(Case const&)=delete;
		
		//Destructeur
		virtual ~Case ();
		
		//Méthodes
		virtual void ajouter_par(Particule* const&);
		
		virtual bool passe_au_suivant(Particule& p) const;
		
		virtual void case_suiv(Case*);
		virtual void case_preced(Case*);
		
		Collection_P particules() const;
		
		//DESSINER
		virtual void dessine() override { if(support_!=nullptr) support_->dessine(*this); }
		
		//AFFICHER POUR LES TESTS
		std::ostream& affiche(std::ostream&) const;
};

