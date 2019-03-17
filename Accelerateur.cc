#include "Accelerateur.h"
#include <string>
using namespace std;

//=======================================================================

//Methodes

ostream& Accelerateur::afficher(ostream& sortie) const {
	if (elements.empty() and particules.empty()) {
		sortie << "L'accélérateur est vide!";
		return sortie;
	}
	string str1="élément"; 
	string str2="particule";
	afficher_boucle(sortie, str1, elements_);
	afficher_boucle(sortie, str2, particules_);
	return sortie;
}

void Accelerateur::afficher_boucle(ostream& sortie, string const& str, Collection_E const& elements) {
	string str3="suivant";
	sortie << "L'accélérateur contient ";
	if (elements.size()==1) {sortie << "l'"+str+" "+str3;};
	else {sortie << "les " << elements.size() << ' '+str+'s'+' '+str3+'s'}
	for (auto const& el : elements) {
		el->affiche(sortie);
	}
}

void Accelerateur::afficher_boucle(ostream& sortie, string const& str, Collection_P const& particules) {
	string str3="suivante";
	sortie << "L'accélérateur contient ";
	if (particules.size()==1) {sortie << "la "+str+" "+str3;};
	else {sortie << "les " << particules.size() << ' '+str+'s'+' '+str3+'s'}
	sortie << " :" << endl;
	for (auto const& par : particules) {
		sortie << *par << endl;
	}
}

void Accelerateur::ajouter_par(p_Particule const& par) {
	particules_.push_back(par);
}

void Accelerateur::ajouter_el(p_Element const& el) {
	elements_.push_back(el);
}

void Accelerateur::supprimer_par() {
	for (auto const& par : particules_) {
		delete par;
	}
	particules.clear();
}

void Accelerateur::supprimer_el() {
	for (auto const& el : elements_) {
		delete el;
	}
	elements.clear();
}

//=======================================================================

//Operateurs Externes

ostream& operator << (ostream& sortie, Accelerateur const& a) {
	return a.affiche(sortie);
}
