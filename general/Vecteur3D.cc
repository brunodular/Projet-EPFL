#include <iostream>
#include "Vecteur3D.h"
#include "constantes.h"
#include <cmath>
using namespace std;

//=======================================================================

//getteurs
double Vecteur3D::x() const {return x_;}
double Vecteur3D::y() const {return y_;}
double Vecteur3D::z() const {return z_;}

//METHODES

ostream& Vecteur3D::affiche(ostream& out) const {
  return (out << ' ' << x_ << ' ' << y_ << ' ' << z_ << ' ');
}

Vecteur3D const Vecteur3D::unitaire() const {
  if (!est_zero(norme(),EPS)) {
    return (*this * (1/norme()));
  } else {
    throw "Division par zéro";
  }
}


double Vecteur3D::norme() const {
  return sqrt(norme2());
}


double Vecteur3D::norme2() const {
  return (*this * *this);
}


Vecteur3D const Vecteur3D::rotation(Vecteur3D const& v, double t) const {
	return cos(t)*(*this)+(1-cos(t))*((*this)*(~v))*(~v)+sin(t)*((~v)^(*this));
}

//=======================================================================

//OPERATEUR INTERNE

bool Vecteur3D::operator==(Vecteur3D const& v) const {
  return (est_zero(x_ - v.x_, EPS) and est_zero(y_ - v.y_, EPS), est_zero(z_ - v.z_, EPS));
}


bool Vecteur3D::operator!=(Vecteur3D const& v) const {return !(*this == v);}


Vecteur3D& Vecteur3D::operator+=(Vecteur3D const& v) {
  x_ += v.x_; y_ += v.y_; z_ += v.z_;
  return *this;
}


Vecteur3D& Vecteur3D::operator-=(Vecteur3D const& v) {
  return (*this += (-v));
}


Vecteur3D& Vecteur3D::operator*=(double a) {
  x_ *= a; y_ *= a; z_ *= a;
  return *this;
}


Vecteur3D& Vecteur3D::operator^=(Vecteur3D const& v) {
  return (*this = Vecteur3D(y_*v.z_-z_*v.y_, z_*v.x_-x_*v.z_, x_*v.y_-y_*v.x_));
}


Vecteur3D const Vecteur3D::operator-() const {
  return Vecteur3D(-x_,-y_,-z_);
}


Vecteur3D const Vecteur3D::operator+(Vecteur3D v) const {
  return (v += *this);
}


Vecteur3D const Vecteur3D::operator-(Vecteur3D v) const {
  return -(v -= *this);
}


Vecteur3D const Vecteur3D::operator*(double a) const {
  return Vecteur3D(a*x_,a*y_,a*z_);
}


double Vecteur3D::operator*(Vecteur3D const& v) const {
  return (x_* v.x_ + y_* v.y_ + z_* v.z_);
}


Vecteur3D const Vecteur3D::operator^(Vecteur3D v) const {
  return -(v ^= *this);
}

Vecteur3D const Vecteur3D::operator~() const {
	return (*this).unitaire();
}

//=======================================================================

//OPERATEUR EXTERNE

ostream& operator<<(ostream& out, Vecteur3D const& v) {return v.affiche(out);}


Vecteur3D const operator*(double c, Vecteur3D v) {
  return (v *= c);
}

//=======================================================================

//FONCTIONS

double prod_mixte(Vecteur3D const& u, Vecteur3D const& v, Vecteur3D const& w) {
  return (u * (v ^ w));
}
