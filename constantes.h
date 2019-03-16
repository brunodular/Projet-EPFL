#pragma once
#include <string>

constexpr double EPS(1e-20);

bool est_zero(double,double eps = EPS);

constexpr double c=299792458;    		//vitesse de la lumiere
constexpr double e=1.60217653e-19;		//charge elementaire

struct Erreur {
  std::string message;
  int type;
};

/*
Types d'erreurs :
1 : arithmétique, e.g. division par 0
2 : construction de variable illicite, e.g. particule de masse nulle
*/
