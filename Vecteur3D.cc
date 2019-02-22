#include <iostream>
#include "Vecteur3D.h"
#include <cmath>
using namespace std;

void Vecteur3D::affiche() const {
  cout << x_ << ' ' << y_ << ' ' << z_;
}

bool Vecteur3D::compare(Vecteur3D autre) const {
  return x_ == autre.x() and y_ == autre.y() and z_ == autre.z();
}

void Vecteur3D::set(double x,double y,double z) {
  x_ = x; y_ = y; z_ = z;
}

Vecteur3D Vecteur3D::addition(Vecteur3D autre) const {
  Vecteur3D resultat;
  resultat.x(x_+autre.x());
  resultat.y(y_+autre.y());
  resultat.z(z_+autre.z());
  return resultat;
}

Vecteur3D Vecteur3D::soustraction(Vecteur3D autre) const {
  return addition(autre.oppose());
}

Vecteur3D Vecteur3D::oppose() const {
  Vecteur3D resultat;
  resultat.x(-x_);
  resultat.y(-y_);
  resultat.z(-z_);
  return resultat;
}

Vecteur3D Vecteur3D::mult(double a) const {
  Vecteur3D resultat;
  resultat.x(a*x_);
  resultat.y(a*y_);
  resultat.z(a*z_);
  return resultat;
}

double Vecteur3D::prod_scal(Vecteur3D autre) const {
  return x_*autre.x() + y_*autre.y() + z_*autre.z();
}

Vecteur3D Vecteur3D::prod_vect(Vecteur3D v) const {
  Vecteur3D resultat;
  resultat.x(y_*v.z()-z_*v.y());
  resultat.y(z_*v.x()-x_*v.z());
  resultat.z(x_*v.y()-y_*v.x());
  return resultat;
}

double Vecteur3D::norme() const {
  return sqrt(norme2());
}

double Vecteur3D::norme2() const {
  return x_*x_ + y_*y_ + z_*z_;
}

Vecteur3D Vecteur3D::unitaire() const {
  Vecteur3D resultat;
  double a(norme());
  resultat.x(x_/a);
  resultat.y(y_/a);
  resultat.z(z_/a);
  return resultat;
}

//setters

void Vecteur3D::x(double x) {x_ = x;}
void Vecteur3D::y(double y) {y_ = y;}
void Vecteur3D::z(double z) {z_ = z;}

//getters

double Vecteur3D::x() const {return x_;}
double Vecteur3D::y() const {return y_;}
double Vecteur3D::z() const {return z_;}


//fonctions

double prod_mixte(Vecteur3D v1, Vecteur3D v2, Vecteur3D v3) {
  return v1.prod_scal(v2.prod_vect(v3));
}
