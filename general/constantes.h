#pragma once

#include "Support_a_dessin.h"
#include <string>
#include <vector>

typedef unsigned int uint;

//=======================================================================

//CONSTANTES UTILISEES
	//CONSTANTE POUR VERIFIER SI C'EST EGAL A 0
constexpr double EPS(1e-20);

	//CONSTANTE POUR LE NOMBRE DE CASES REPRESENTEES
constexpr double NB_CASES=100000;

	//CONSTANTES PHYSIQUES
constexpr double c=299792458;    		//vitesse de la lumiere en m.s^-1
constexpr double e=1.60217653e-19;		//charge elementaire en Coulomb
constexpr double e_0=8.85e-12;			//permittivité du vide en F.m^-1

	//CONSTANTES POUR L'AFFICHAGE TEXTE
constexpr uint MARGE=25;

//=======================================================================

//FONCTION POUR EVALUER SI C'EST EGAL A 0
bool est_zero(double,double eps = EPS);

//=======================================================================

//TYPEDEF UTILISES DANS BEAUCOUP DE CLASSES DE NOTRE PROJET
typedef Particule* p_Particule;	//On a choisi de mettre des pointeurs afin d'optimiser la simulation et puis dans la cas ou l'on voudrait cree dans sous-classes de Particule afin d'utiliser le polymorphisme
typedef Element* p_Element;		//On a choisi de mettre des pointeurs a la C a la place de unique_ptr car les elements sont pointe par d'autres pointeurs (pointeur sur l'element courant et suivant par les Particules et les Elements respectivement cf. definition de la classe Element et Particule)
typedef Faisceau* p_Faisceau;
typedef double Abs;

typedef std::vector<p_Element> Collection_E;
typedef std::vector<p_Faisceau> Collection_F;
typedef std::vector<p_Particule> Collection_P;

//=======================================================================

//STRUCTURE POUR MODULARISER QUELQUES METHODES DANS ACCELERATEUR
struct No_name {
	size_t i_;
	double x_;
};

//STRUCTURE D'ERREUR POUR LES EXCEPTIONS
struct Erreur {
  std::string message;
  int type;
};

/*
Types d'erreurs :
1 : arithmétique, e.g. division par 0
2 : construction de variable illicite, e.g. particule de masse nulle
*/
