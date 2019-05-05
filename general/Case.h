#pragma once

#include "Particule.h"
#include "Dessinable.h"
#include <vector>
#include <iostream>

typedef std::vector<Particule*> Collection_P;


class Case : public Dessinable {
	private:
		Collection_P particules_;
		Abs abs_e_;
		Abs abs_s_;
		Vecteur3D pos_e_;
		Vecteur3D pos_s_;
		Case* case_suiv_;
		Case* case_preced_;
	
	public:
		
		//Getters
		Abs abs_e () const;
		Abs abs_s () const;
		Vecteur3D pos_e() const;
		Vecteur3D pos_s() const;
		Collection_P particules() const;
		
		//Constructeur
		Case (Abs, Abs, Accelerateur* const&  acc=nullptr);
		Case(Case const&)= delete;
		Case& operator=(Case const&)=delete;
		
		//Destructeur
		virtual ~Case ();
		
		//Méthodes
		virtual void ajouter_par(Particule* const&);
		
		virtual bool passe_au_suivant(Particule& p) const;
		
			//Setter
		virtual void case_suiv(Case*);
		virtual void case_preced(Case*);
		
		//DESSINER
		virtual void dessine() override { if(support_!=nullptr) support_->dessine(*this); }
		
		//AFFICHER POUR LES TESTS
		std::ostream& affiche(std::ostream&) const;
};

