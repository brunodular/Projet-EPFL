#include "../inc/Accelerateur.h"
#include <string>
using namespace std;

//=======================================================================

//Constructeur
Accelerateur::Accelerateur (Collection_P const& p, Collection_E const& e, SupportADessin* support)
  : Dessinable(support), particules_(p), elements_(e) {}

Accelerateur::Accelerateur(SupportADessin* support) : Dessinable(support) {}

//Destructeur
Accelerateur::~Accelerateur () {
  for (auto el : elements_) {
    delete el;
  }
  elements_.clear();
  for (auto par : particules_) {
    delete par;
  }
  particules_.clear();
}

//Methodes

ostream& Accelerateur::affiche(ostream& sortie) const {
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
			el->dessine();
		}

	} else {sortie << "L'accélérateur ne contient pas d'éléments." << endl;}

	if (particules_.size()!=0) {
		sortie << "L'accélérateur contient ";
		if (particules_.size()==1) {sortie << "la "+str2+" "+str4;}
		else {sortie << "les " << particules_.size() << ' '+str2+'s'+' '+str4+'s';}
		sortie << " :" << endl;

		for (auto const& par : particules_) {
			par->dessine();
		}

	} else {sortie << "L'accélérateur ne contient pas de particules." << endl;}

	return sortie;
}

void Accelerateur::ajouter_par(p_Particule const& par) {
	particules_.push_back(par);
}

//J'ai modifié cette méthode car 'new Element(*el)' créait un pointeur vers un Element, et donc si on donnait un pointeur vers un Dipole par exemple, le Dipole était mis dans un Element et perdait donc ses attributs caractéristiques

void Accelerateur::ajouter_el(p_Element const& el) {
	elements_.push_back(el);
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

ostream& operator<<(ostream& sortie, Accelerateur const& a) {
	return a.affiche(sortie);
}
