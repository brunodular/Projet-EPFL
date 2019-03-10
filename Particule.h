#pragma once

#include "Vecteur3D.h"
#include <iostream>

typedef double Masse;

class Particule {
	private:
		Vecteur3D pos_;   //position a un instant t
		Vecteur3D v_;			//vitesse au moment t
		Masse M_;         //Masse: est-îl mieux de mettre const double? Et comment faire positif?
		double Q_;        //charge
		double E_;				//energie de la particule
		double gamma_;  	//facteur gamma de relativite
		Vecteur3D force_;

		static constexpr double c=299792458;		//vitesse de la lumiere comme constante commune a toutes les particules
		static constexpr double e=1.60217653e-19;		//charge elementaire comme constante

	public:
		//Constructeurs
		Particule (Masse M, double Q,Vecteur3D pos=Vecteur3D (0.0, 0.0, 0.0), Vecteur3D vt=Vecteur3D (0.0, 0.0, 0.0),Vecteur3D force=Vecteur3D(0.0, 0.0, 0.0),double g=1.0, double E=0.0) : pos_(pos), v_(vt), M_(M), Q_(Q), E_(E), gamma_(g), force_(force) {}

		//Methodes
			//Setters
		void E();
		void v(); 			//j'ai decide d'utiliser la quantite de mvt pour la specification de v
		void gamma();

			//Evolution de la particule
		void ajouteForceMagnetique(Vecteur3D const&, double);
		void bouger(double);

			//Getters
		double E() const {return E_;}
		Vecteur3D v() const {return v_;}
		double gamma() const {return gamma_;}
		Vecteur3D quantite_mvt();

		std::ostream& afficher(std::ostream&) const;

		//Operateurs internes

};

//Operateurs externes
std::ostream& operator<<(std::ostream&, Particule const&);

//const double Particule::c=299792458;
//const double Particule::e=1.60217653e-19;
