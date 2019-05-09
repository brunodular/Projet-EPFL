#pragma once

#include "Particule.h"
#include "Dessinable.h"
#include <vector>
#include <iostream>

class Case : public Dessinable {
	private:
		vector<Collection_P> particules_;
		
	public:
		
		
		//Constructeur
		Case(Case const&)= delete;
		Case& operator=(Case const&)=delete;
		
		//Destructeur
		~Case ();
		
		//Méthodes
		virtual void ajouter_par(Particule* const&);

		//AFFICHER POUR LES TESTS
		std::ostream& affiche(std::ostream&) const;
};

