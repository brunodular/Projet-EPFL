#include "Accelerateur.h"
#include "Support_a_dessin.h"
#include <string>
#include <vector>
using namespace std;

//=======================================================================

//Constructeur
Accelerateur::Accelerateur (Collection_P const& p, Collection_E const& e, SupportADessin* support)
  : Dessinable(support), particules_(p), elements_(e) {}

Accelerateur::Accelerateur(SupportADessin* support) : Dessinable(support) {}

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

std::ostream& Accelerateur::affiche_part(std::ostream& sortie) const {
  string str1="element";
	string str2="particule";
	string str3="suivant";
	string str4=str3+'e';

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
  par->set_support(support);
	particules_.push_back(par);
}

//J'ai modifié cette méthode car 'new Element(*el)' créait un pointeur vers un Element, et donc si on donnait un pointeur vers un Dipole par exemple, le Dipole était mis dans un Element et perdait donc ses attributs caractéristiques

void Accelerateur::ajouter_el(p_Element const& el) {
  el->set_support(support);
	elements_.push_back(el);
}

//CONSTRUIRE

void Accelerateur::souder_accelerateur() {
  size_t n(elements_.size()); //nombre d'élément contenus dans l'accélérateur
  if (n != 0) {
    elements_.back()->el_suiv(elements_[0]);
    for (size_t i(0); i<n-1; ++i) {
      elements_[i]->el_suiv(elements_[i+1]);
    }
  }
}


void Accelerateur::initialiser_particules() {
  if (elements_.size() != 0) {
    for (auto& p : particules_) {
      p->element_courant(elements_.front());
      while(p->element_courant()->passe_au_suivant(*p));
    }
  }
}


//Supprimer

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

void Accelerateur::supprimer_par(size_t i) {
  delete particules_[i];
  particules_.erase(particules_.begin() + i);
}

//EVOLUTION

void Accelerateur::evolue(double dt) {
  size_t i(0);
  while (i < particules_.size()) {
    if (not particules_[i]->est_sortie()) { //vérifie si la particule est toujours dans l'accélérateur
      Particule* p = particules_[i];

      p->ajouter_f_magn((p->element_courant())->B(*p),dt); //On ajoute à la particule p le champ magnétique produit par l'élément dans lequel elle se trouve.

      p->bouger(dt); //On modifie la position et la vitesse de la particule en fonction de la force quis s'exerce dessus.

      if (p->element_courant()->passe_au_suivant(*p)) //Mise à jour de l'élément courant de la particule p.

      ++i;
    } else {
      supprimer_par(i);
    }
  }
}

//=======================================================================

//Operateurs Externes

ostream& operator<<(ostream& sortie, Accelerateur const& a) {
	return a.affiche(sortie);
}
