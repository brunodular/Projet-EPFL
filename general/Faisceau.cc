#include "Faisceau.h"
#include <cmath>
#include <vector>
using namespace std;

//=======================================================================

//Méthodes privées, utilisées dans les autres méthodes
  //paramètres verticaux
double Faisceau::moyenne_pos_2_z() const {
  if (nombre_particules() == 0) return 0.0;
  else {
    double moyenne(0.0);
    for (auto& p : particules_) {
      if (p->element_courant() != nullptr) {
        double pos(p->pos().z());
        moyenne += pos*pos;
      }
    }
    return (moyenne / nombre_particules());
  }
}
double Faisceau::moyenne_vit_2_z() const {
  if (nombre_particules() == 0) return 0.0;
  else {
    double moyenne(0.0);
    for (auto& p : particules_) {
      if (p->element_courant() != nullptr) {
        double vit(p->v().z());
        moyenne += vit*vit;
      }
    }
    return (moyenne / nombre_particules());
  }
}
double Faisceau::moyenne_pos_vit_z() const {
  if (nombre_particules() == 0) return 0.0;
  else {
    double moyenne(0.0);
    for (auto& p : particules_) {
      if (p->element_courant() != nullptr) {
        double pos(p->pos().z());
        double vit(p->v().z());
        moyenne += pos*vit;
      }
    }
    return (moyenne / nombre_particules());
  }
}

//paramètres radiaux
double Faisceau::moyenne_pos_2_r() const {
  if (nombre_particules() == 0) return 0.0;
  else {
    double moyenne(0.0);
    for (auto& p : particules_) {
      if (p->element_courant() != nullptr) {
        double pos(p->element_courant()->coord_orthogonale_position(p));
        moyenne += pos*pos;
      }
    }
    return (moyenne / nombre_particules());
  }
}
double Faisceau::moyenne_vit_2_r() const {
  if (nombre_particules() == 0) return 0.0;
  else {
    double moyenne(0.0);
    for (auto& p : particules_) {
      if (p->element_courant() != nullptr) {
        double vit(p->element_courant()->coord_orthogonale_vitesse(p));
        moyenne += vit*vit;
      }
    }
    return (moyenne / nombre_particules());
  }
}

double Faisceau::moyenne_pos_vit_r() const {
  if (nombre_particules() == 0) return 0.0;
  else {
    double moyenne(0.0);
    for (auto& p : particules_) {
      if (p->element_courant() != nullptr) {
        double pos(p->element_courant()->coord_orthogonale_position(p));
        double vit(p->element_courant()->coord_orthogonale_vitesse(p));
        moyenne += pos*vit;
      }
    }
    return (moyenne / nombre_particules());
  }
}

//=======================================================================

//Constructeur

Faisceau::Faisceau(p_Particule p, double x, unsigned int nombre, const unsigned int lambda, double dl, Accelerateur const& acc, SupportADessin* support_)
	: Dessinable(support_), particule_typique_(p), lambda_(lambda)
{
  unsigned int macro_nombre(nombre/lambda);
  double dx(dl/macro_nombre);

	for (size_t i(0); i<macro_nombre; ++i) {
		particules_.push_back(p_Particule (new Particule(acc, x - 0.5*dl + i*dx, p->v(), p->E()*lambda, p->m()*lambda, p->q()*lambda)));
  }
}
Faisceau::Faisceau (SupportADessin* support) : Dessinable(support) {}

Faisceau::Faisceau (Faisceau const& autre) {
	this->supprimer_par();
	for (auto const& par : autre.particules()) {
		particules_.push_back(new Particule(*par));
	}
}

//=======================================================================

//Methodes

ostream& Faisceau::affiche(ostream& sortie) const{
	for (auto& p : particules_) {
		p->affiche(sortie);
	}
	return sortie;
}

void Faisceau::set_support(SupportADessin* sup) {
	support_=sup;
	for (auto& par : particules_) {
		par->set_support(sup);
	}
}

ostream& Faisceau::affiche_part(std::ostream& sortie) const {
	string str1="element";
	string str2="particule";
	string str3="suivant";
	string str4=str3+'e';

  if (particules_.size()!=0) {
		sortie << "Le faisceau contient ";
		if (particules_.size()==1) {sortie << "la "+str2+" "+str4;}
		else {sortie << "les " << particules_.size() << ' '+str2+'s'+' '+str4+'s';}
		sortie << " :" << endl;

		for (auto const& par : particules_) {
			par->dessine();
		}

	} else {sortie << "Le faisceau ne contient pas de particules." << endl;}

	return sortie;
}

//========================================================================

//GETTERS

Collection_P Faisceau::particules() const{return particules_;}

double Faisceau::E_moyenne() const {
	double moyenne(0.0);
	cout << "Nombre de particules " << nombre_particules() << endl;
	
  if (nombre_particules() != 0) {
    for (auto& p : particules_) {
      moyenne += p->E();
    }
    moyenne /= nombre_particules();
  } 
  return moyenne;
}

double Faisceau::emittance_z() const {
  return sqrt(moyenne_pos_2_z()*moyenne_vit_2_z() - moyenne_pos_vit_z()*moyenne_pos_vit_z());
}

double Faisceau::emittance_r() const {
  return sqrt(moyenne_pos_2_r()*moyenne_vit_2_r() - moyenne_pos_vit_r()*moyenne_pos_vit_r());
}


double Faisceau::A_11_r() const {
  return (moyenne_vit_2_r()/emittance_r());
}

double Faisceau::A_12_r() const {
  return (- moyenne_pos_vit_r()/emittance_r());
}

double Faisceau::A_22_r() const {
  return (moyenne_pos_2_r()/emittance_r());
}

double Faisceau::A_11_z() const {
  return (moyenne_vit_2_z()/emittance_z());
}

double Faisceau::A_12_z() const {
  return (- moyenne_pos_vit_z()/emittance_z());
}
double Faisceau::A_22_z() const {
  return (moyenne_pos_2_z()/emittance_z());
}

unsigned int Faisceau::nombre_particules() const {
	return particules_.size();
}

unsigned int Faisceau::nombre_particules_simulees() const {
  return lambda_ * nombre_particules();
}

//=======================================================================

//Modifier la collection de particules
void Faisceau::supprimer_par(size_t i) {
  delete particules_[i];
  particules_.erase(particules_.begin() + i);
}

void Faisceau::supprimer_par() {
	for (auto& par : particules_) {
		delete par;
	}
	particules_.clear();
}

void Faisceau::ajouter_par(p_Particule const& par) {
	par->set_support(support_);
	particules_.push_back(par);
}

void Faisceau::initialiser_particules(p_Element const& el) {
	for (auto& p : particules_) {
      p->element_courant(el);
      while(p->element_courant()->passe_au_suivant(*p));
	}
}

//=======================================================================

//EVOLUTION
void Faisceau::evolue(double dt, Accelerateur* const& acc) {
  size_t i(0);
  while(i<nombre_particules()) {
    if ((not particules_[i]->est_sortie())) { //vérifie si la particule est toujours dans l'accélérateur
	  
      particules_[i]->ajouter_f_magn((particules_[i]->element_courant())->B(*particules_[i]),dt); //On ajoute à la particule p le champ magnétique produit par l'élément dans lequel elle se trouve.

      particules_[i]->bouger(dt); //On modifie la position et la vitesse de la particule en fonction de la force quis s'exerce dessus.
      
      particules_[i]->element_courant()->passe_au_suivant(*particules_[i]); //Mise à jour de l'élément courant de la particule p.
      
      ++i;
    
    } else {
		Erreur err {"CASE COURANTE EST NULLPTR", 8};
		throw err;
		
		//supprimer_par(i);
		//cout << nombre_particules() << endl;
	}
  }
}

void Faisceau::force_inter_particulaire(double a, double b) {
	for (auto const& p : particules_) {
		if (acc->pos_en_abs(*p)>a and acc->pos_en_abs(*p)<=b) {
			  particules[i]->ajouter_force_inter_particulaire(*p);
		}
	}
}

//=======================================================================

//DESSINER

void Faisceau::dessine_particule() const {
	if(nombre_particules()!=0 and support_!=nullptr) {
		for (auto const& p : particules_) {
			support_->dessine(*p);
		}
	}
}
