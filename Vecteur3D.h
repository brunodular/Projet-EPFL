class Vecteur3D {
private:
  double x_, y_, z_;

public:
  void affiche() const;
  bool compare(Vecteur3D autre) const;
  void set(double x,double y,double z);

  Vecteur3D addition(Vecteur3D autre) const;
  Vecteur3D soustraction(Vecteur3D autre) const;
  Vecteur3D oppose() const;
  Vecteur3D mult(double a) const;
  double prod_scal(Vecteur3D autre) const;
  Vecteur3D prod_vect(Vecteur3D autre) const;

  double norme() const;
  double norme2() const;

  Vecteur3D unitaire() const;

//setters
  void x(double x);
  void y(double y);
  void z(double z);

//getters
  double x() const;
  double y() const;
  double z() const;
};

double prod_mixte(Vecteur3D v1, Vecteur3D v2, Vecteur3D v3);
