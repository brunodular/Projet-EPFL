#include "Accelerateur.h"
#include "Support_a_dessin.h"
#include <string>
#include <vector>
#include <cmath>
using namespace std;

//=======================================================================

//Constructeur
Accelerateur::Accelerateur (Collection_F const& f, Collection_E const& e, SupportADessin* support)
  : Dessinable(support), faisceaux_(f), elements_(e), longueur_(0.0), cases_(NB_CASES) {}

Accelerateur::Accelerateur(SupportADessin* support) : Dessinable(support), longueur_(0.0), cases_(NB_CASES) {}

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
  size_t n(elements_.size()); //nombre d'éléments contenus dans l'accélérateur
  if (n != 0) {
    for (size_t i(1); i<n; ++i) {
      elements_[i]->el_suiv(elements_[(i+1)%n]);
      elements_[i]->el_prec(elements_[(i-1)%n]);
      longueur_ += elements_[i]->longueur();
    }
    elements_[0]->el_prec(elements_[n-1]);
    elements_[0]->el_suiv(elements_[1]);
    longueur_ += elements_[0]->longueur();
  }
}

Vecteur3D Accelerateur::abs_en_pos(double x) const {
  x *= longueur_;
  if (x < 0) x += longueur_;
  size_t i(0);
  while (x > elements_[i]->longueur()) {
    x -= elements_[i]->longueur();
    i = (i+1)%elements_.size();
  }
  return elements_[i]->abs_en_pos(x / elements_[i]->longueur());
}

Abs Accelerateur::pos_en_abs(p_Particule const& p) const {
  size_t num_element(0);
  while (elements_[num_element]->pos_e() != p->element_courant()->pos_e()) ++num_element;

  double abs(0);
  for (size_t i(0); i<num_element; ++i) abs += elements_[i]->longueur();
  abs += p->element_courant()->pos_en_abs(p);
  abs /= longueur_;
  return abs;
}


void Accelerateur::initialiser_particules() {
  if (elements_.size() != 0) {
	  for (auto& f : faisceaux_) {
		  f->initialiser_particules(*this,cases_);
    }
  }
}

//MEGA-Constructeurs
void Accelerateur::construire_polygone(size_t n, double R) {
  double theta(2*M_PI/n); //angle au centre(de courbure) intercepte par un dipole
  double rho(M_PI/10); //angle au centre(origine) intercepte par un dipole
  double d(2*R*sin(rho/2)); //distance entre les entrees et sorties des dipoles
  double k(2*sin(theta/2)/d); //courbure des dipoles

  for (size_t i(0); i<n; ++i) {
    double angle_e(i*theta - theta/2 - 0.5*rho), angle_s(i*theta - theta/2 + 0.5*rho), angle_e2((i+1)*theta - theta/2 - 0.5*rho);
    Vecteur3D pos_e(cos(angle_e),-sin(angle_e),0); Vecteur3D pos_s(cos(angle_s),-sin(angle_s),0); Vecteur3D pos_e2(cos(angle_e2),-sin(angle_e2),0);
    ajouter_el(new Dipole(R*pos_e,R*pos_s,0.3,k,5.89158));
    ajouter_el(new MailleFODO(R*pos_s,R*pos_e2,0.3,1.2,0.9));
    //ajouter_el(new SectionDroite(R*Vecteur3D(cos(angle_s),sin(angle_s),0),R*Vecteur3D(cos(angle_e2),sin(angle_e2),0),0.3));
  }
  souder_accelerateur();
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
    f->evolue(*this,cases_,dt);
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
