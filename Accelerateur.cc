#include "Accelerateur.h"
#include <string>
using namespace std;

//=======================================================================

//Constructeur
Accelerateur::Accelerateur (Collection_P const& p, Collection_E const& e)
  : particules_(p), elements_(e) {}

//Methodes

ostream& Accelerateur::afficher(ostream& sortie) const {
	if (elements_.empty() and particules_.empty()) {
		sortie << "L'accélérateur est vide!";
		return sortie;
	}
	string str1="element";
	string str2="particule";
	string str3="suivant";
	string str4=str3+'e';
	if (elements_.size()!=0) {
		sortie << "L'accélérateur contient ";
		if (elements_.size()==1) {sortie << "l'"+str1+" "+str3;}
		else {sortie << "les " << elements_.size() << ' '+str1+'s'+' '+str3+'s';}
		sortie << " : "<< endl;
		for (auto const& el : elements_) {
			el->affiche(sortie);
		}
	} else {sortie << "L'accélérateur ne contient pas d'éléments." << endl;}
	
	if (particules_.size()!=0) {
		sortie << "L'accélérateur contient ";
		if (particules_.size()==1) {sortie << "la "+str2+" "+str4;}
		else {sortie << "les " << particules_.size() << ' '+str2+'s'+' '+str4+'s';}
		sortie << " :" << endl;
		for (auto const& par : particules_) {
			sortie << (*par) << endl;
		}
	} else {sortie << "L'accélérateur ne contient pas de particules." << endl;}
	
	return sortie;
}

void Accelerateur::ajouter_par(p_Particule const& par) {
	particules_.push_back(p_Particule (new Particule(*par)));
}

void Accelerateur::ajouter_el(p_Element const& el) {
	elements_.push_back(p_Element (new Element (*el)));
}

void Accelerateur::supprimer_par() {
	for (auto const& par : particules_) {
		delete par;
	}
	particules_.clear();
}

void Accelerateur::supprimer_el() {
	for (auto const& el : elements_) {
		delete el;
	}
	elements_.clear();
}

//=======================================================================

//Operateurs Externes

ostream& operator << (ostream& sortie, Accelerateur const& a) {
	return a.afficher(sortie);
}
