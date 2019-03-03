#include <iostream> 

class Vecteur3D {
	private:
		double x_, y_, z_;

	public:
		//Constructeurs
		Vecteur3D(double x = 0.0, double y = 0.0, double z = 0.0) : x_(x), y_(y), z_(z) {}

		//méthodes
		std::ostream& affiche(std::ostream&) const;
		Vecteur3D const unitaire() const;			//vecteur unitaire
		double norme() const;
		double norme2() const;

		//opérateurs internes
		bool operator==(Vecteur3D const&) const;
		bool operator!=(Vecteur3D const&) const;

		Vecteur3D& operator+=(Vecteur3D const&);
		Vecteur3D& operator-=(Vecteur3D const&);
		Vecteur3D& operator*=(double);
		Vecteur3D& operator^=(Vecteur3D const&);

		Vecteur3D const operator-() const;			//oppose
		Vecteur3D const operator+(Vecteur3D) const;
		Vecteur3D const operator-(Vecteur3D) const;
		Vecteur3D const operator*(double) const;	//multiplcation par 
													//un scalaire
														
		double operator*(Vecteur3D const&) const;	//produit scalaire
		Vecteur3D const operator^(Vecteur3D) const;	//produit vectoriel

};

//opérateurs externes
std::ostream& operator<<(std::ostream&, Vecteur3D const&);
Vecteur3D const operator*(double, Vecteur3D);

//fonctions
double prod_mixte(Vecteur3D const&, Vecteur3D const&, Vecteur3D const&);
												// produit mixte
