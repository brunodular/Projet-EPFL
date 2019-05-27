#pragma once

#include <iostream>

class Vecteur3D {
	private:
		double x_, y_, z_;
		Vecteur3D const unitaire() const;			//methode qui permet de trouver le vecteur unitaire utilise dans l'operateur ~

	public:
		//Constructeurs
		Vecteur3D(double x = 0.0, double y = 0.0, double z = 0.0) : x_(x), y_(y), z_(z) {}

		//getteurs
		double x() const;
		double y() const;
		double z() const;

		//méthodes
		std::ostream& affiche(std::ostream&) const;
		double norme() const;
		double norme2() const;
		Vecteur3D const rotation(Vecteur3D const&, double) const; //methode qui effectuve une rotation dans l'axe du vecteur donne en parametre d'angle le double donne en parametre

		//opérateurs internes
		bool operator==(Vecteur3D const&) const;
		bool operator!=(Vecteur3D const&) const;

		Vecteur3D& operator+=(Vecteur3D const&);
		Vecteur3D& operator-=(Vecteur3D const&);
		Vecteur3D& operator*=(double); 				//produit scalaire
		Vecteur3D& operator^=(Vecteur3D const&);	//produit vectoriel

		Vecteur3D const operator-() const;			//opposé
		Vecteur3D const operator+(Vecteur3D) const;
		Vecteur3D const operator-(Vecteur3D) const;
		Vecteur3D const operator*(double) const;	//multiplication par un scalaire
		Vecteur3D const operator~() const;			//vecteur unitaire

		Vecteur3D const orthogonal() const;			//retourne un vecteur orthogonal

		double operator*(Vecteur3D const&) const;	//produit scalaire
		Vecteur3D const operator^(Vecteur3D) const;	//produit vectoriel
};

//opérateurs externes
std::ostream& operator<<(std::ostream&, Vecteur3D const&);
Vecteur3D const operator*(double, Vecteur3D);

//fonctions
double prod_mixte(Vecteur3D const&, Vecteur3D const&, Vecteur3D const&);

//Vecteurs de base
const Vecteur3D e1(1,0,0), e2(0,1,0), e3(0,0,1);
