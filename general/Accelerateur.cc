#include "Accelerateur.h"
#include "Support_a_dessin.h"
#include <string>
#include <vector>
using namespace std;

//=======================================================================

//Constructeur
Accelerateur::Accelerateur (Collection_F const& f, Collection_E const& e, SupportADessin* support)
  : Dessinable(support), faisceaux_(f), elements_(e), longueur_(0.0) {}

Accelerateur::Accelerateur(SupportADessin* support) : Dessinable(support), longueur_(0.0) {}

//Getters
Collection_E Accelerateur::elements() const {
  return elements_;
}
Collection_F Accelerateur::faisceaux() const {
  return faisceaux_;
}

//Methodes

ostream& Accelerateur::affiche(ostream& sortie) const {
	if (elements_.empty() and faisceaux_.empty()) {
		sortie << "L'accélérateur est vide!";
		return sortie;
	}
	string str1="element";
	string str3="suivant";
	string str4=str3+'e';
	string str5="faisceau";

	if (elements_.size()!=0) {
		sortie << "L'accélérateur contient ";
		if (elements_.size()==1) {sortie << "l'"+str1+" "+str3;}
		else {sortie << "les " << elements_.size() << ' '+str1+'s'+' '+str3+'s';}
		sortie << " : "<< endl;

		for (auto const& el : elements_) {
			el->dessine();
		}

	} else {sortie << "L'accélérateur ne contient pas d'éléments." << endl;}



	if (faisceaux_.size()!=0 and faisceaux_[0]->nombre_particules()!=0) {
		sortie << "L'accelerateur contient : ";
		if (faisceaux_.size()==1) {sortie << "le "+str5+" "+str3;}
		else {sortie << "les " << faisceaux_.size() << ' '+str5+'s'+str3+'s';}
		sortie << " : " << endl;

		for (auto const& f : faisceaux_) {
			//f->dessine();  MARCHE PAS?????
			f->affiche(sortie);
		}
	} else {sortie << "L'accelerateur ne contient pas de faisceaux." << endl;}

	return sortie;
}

std::ostream& Accelerateur::affiche_part(std::ostream& sortie) const {
  if (!(faisceaux_.empty())) {
	  for (auto const& f : faisceaux_) {
		f->affiche_part(sortie);
	}
  }

  return sortie;
}

void Accelerateur::ajouter_faisceau(p_Particule p, double x, unsigned int nombre, const unsigned int lambda, double dl) {
  faisceaux_.push_back(p_Faisceau(new Faisceau(p,x,nombre,lambda,dl,*this)));
  faisceaux_.back()->set_support(support_);
}

//J'ai modifié cette méthode car 'new Element(*el)' créait un pointeur vers un Element, et donc si on donnait un pointeur vers un Dipole par exemple, le Dipole était mis dans un Element et perdait donc ses attributs caractéristiques

void Accelerateur::ajouter_el(p_Element const& el) {
  el->set_support(support_);
	elements_.push_back(el);
}

void Accelerateur::ajouter_faisceau_par(size_t i, p_Particule const& par) {
	faisceaux_[i]->ajouter_par(par);
}

//CONSTRUIRE

void Accelerateur::souder_accelerateur() {
  size_t n(elements_.size()); //nombre d'élément contenus dans l'accélérateur
  if (n != 0) {
    elements_.back()->el_suiv(elements_[0]);
    longueur_ += elements_.back()->longueur();

    for (size_t i(0); i<n-1; ++i) {
      elements_[i]->el_suiv(elements_[i+1]);
      longueur_ += elements_[i]->longueur();
    }
  }
}

Vecteur3D Accelerateur::abs_en_pos(double x) const {
  x *= longueur_;
  if (x < 0) x += longueur_;
  size_t i(0);
  while (x > elements_[i]->longueur()) {
    x -= elements_[i]->longueur();
    ++i;
  }
  return elements_[i]->abs_en_pos(x / elements_[i]->longueur());
}

void Accelerateur::initialiser_particules() {
  if (elements_.size() != 0) {
	  for (auto& f : faisceaux_) {
		  f->initialiser_particules(elements_.front());
    }
  }
}

//Supprimer

void Accelerateur::supprimer_faisceau() {
	faisceaux_.clear();
}

void Accelerateur::supprimer_el() {
	for (auto& el : elements_) {
		delete el;
	}
	elements_.clear();
}

void Accelerateur::supprimer_faisceau(size_t i) {
	faisceaux_.erase(faisceaux_.begin()+i);
}

void Accelerateur::supprimer_faisceau_par(size_t i) {
	faisceaux_[i]->supprimer_par();
}

void Accelerateur::supprimer_faisceau_par(size_t i, size_t j) {
	faisceaux_[i]->supprimer_par(j);
}

//EVOLUTION

void Accelerateur::evolue(double dt) {
  for (auto& f : faisceaux_) {
	f->evolue(dt);
  }
}

//DESSINER
void Accelerateur::dessine_faisceau() const {
	if (faisceaux_.size()!=0 and support_!=nullptr) {
		for (auto const& f : faisceaux_) {
			f->dessine();
		}
	}
}

void Accelerateur::dessine_element() const {
	if (elements_.size()!=0) {
		for (auto const& el : elements_) {
			el->dessine();
		}
	}
}

void Accelerateur::set_support(SupportADessin* sup) {
	support_=sup;
	if (faisceaux_.size()!=0 and sup!=nullptr) {
		for (auto const& f : faisceaux_) {
			f->set_support(sup);
		}
	}
}

//=======================================================================

//Operateurs Externes

ostream& operator<<(ostream& sortie, Accelerateur const& a) {
	return a.affiche(sortie);
}
