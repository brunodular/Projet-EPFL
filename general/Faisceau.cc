#include "Faisceau.h"
#include <cmath>
#include <vector>
using namespace std;

//=======================================================================

//méthodes privées, utilisées dans les autres méthodes
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


//-----------------------------------------------------------------------

Vecteur3D Faisceau::moyenne_vit() const {
if (nombre_particules() == 0) return 0.0;
  else {
    double moyenneX(0.0);
    double moyenneY(0.0);
    double moyenneZ(0.0);
    for (auto const& p : particules_) {
      if (p->element_courant() != nullptr) {
        double pos1(p->v().x());
		double pos2(p->v().y());
		double pos3(p->v().z());
	    moyenneX += pos1;
	    moyenneY += pos2;
	    moyenneZ += pos3;
      } 
    }
    unsigned int Nb=nombre_particules();
    return Vecteur3D (moyenneX/Nb, moyenneY/Nb, moyenneZ/Nb);
  }
}

Vecteur3D Faisceau::moyenne_pos() const {
  if (nombre_particules() == 0) return 0.0;
  else {
    double moyenneX(0.0);
    double moyenneY(0.0);
    double moyenneZ(0.0);
    for (auto const& p : particules_) {
      if (p->element_courant() != nullptr) {
        double pos1(p->pos().x());
		double pos2(p->pos().y());
		double pos3(p->pos().z());
	    moyenneX += pos1;
	    moyenneY += pos2;
	    moyenneZ += pos3;
      } 
    }
    unsigned int Nb=nombre_particules();
    return Vecteur3D (moyenneX/Nb, moyenneY/Nb, moyenneZ/Nb);
  }
}

Vecteur3D Faisceau::F_moyenne () const {
  if (nombre_particules() == 0) return 0.0;
  else {
    double moyenneX(0.0);
    double moyenneY(0.0);
    double moyenneZ(0.0);
    for (auto const& p : particules_) {
      if (p->element_courant() != nullptr) {
        double pos1(p->F().x());
		double pos2(p->F().y());
		double pos3(p->F().z());
	    moyenneX += pos1;
	    moyenneY += pos2;
	    moyenneZ += pos3;
      } 
    }
    unsigned int Nb=nombre_particules();
    return Vecteur3D (moyenneX/Nb, moyenneY/Nb, moyenneZ/Nb);
  }
}

double Faisceau::m_moyenne() const {
  if (nombre_particules() == 0) return 0.0;
  else {
    double moyenne(0.0);
    for (auto& p : particules_) {
      if (p->element_courant() != nullptr) {
        double masse(p->m());
        moyenne += masse;
      }
    }
    return (moyenne / nombre_particules());
  }	
}

double Faisceau::q_moyenne() const {
  if (nombre_particules() == 0) return 0.0;
  else {
    double moyenne(0.0);
    for (auto& p : particules_) {
      if (p->element_courant() != nullptr) {
        double charge(p->q());
        moyenne += charge;
      }
    }
    return (moyenne / nombre_particules());
  }		
}

//=======================================================================

//Constructeur

Faisceau::Faisceau (Collection_P const& particules, unsigned int lambda, SupportADessin* support, p_Particule p)
	: Dessinable(support), lambda_(lambda), particules_(particules), particule_typique_(p)
{particule_typique_=particule_typique();} 

Faisceau::Faisceau (SupportADessin* support) : Dessinable(support) {}

//Destructeur
Faisceau::~Faisceau () {
  for (auto& par : particules_) {
    delete par;
  }
  particules_.clear();
}

//=======================================================================

//Methodes

ostream& Faisceau::affiche(ostream& sortie) const{
	sortie << "Particule typique du faisceau : " << endl;
	particule_typique()->affiche(sortie);
	return sortie;
}

void Faisceau::set_support(SupportADessin* support_) {
	support=support_;
	for (auto& par : particules_) {
		par->set_support(support);
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

p_Particule Faisceau::particule_typique() const {
	return p_Particule(new Particule(moyenne_pos(), moyenne_vit(), E_moyenne(), m_moyenne(), q_moyenne(), support, F_moyenne()));
}

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
	par->set_support(support);
	particules_.push_back(par);
}

void Faisceau::initialiser_particules(p_Element const& el) {
	for (auto& p : particules_) {
      p->element_courant(el);
      while(p->element_courant()->passe_au_suivant(*p));
  }
  particule_typique_=particule_typique();
}

//EVOLUTION
void Faisceau::evolue(double dt) {
  for (auto& p : particules_) {
    if (not p->est_sortie()) { //vérifie si la particule est toujours dans l'accélérateur

      p->ajouter_f_magn((p->element_courant())->B(*p),dt); //On ajoute à la particule p le champ magnétique produit par l'élément dans lequel elle se trouve.

      p->bouger(dt); //On modifie la position et la vitesse de la particule en fonction de la force quis s'exerce dessus.

      p->element_courant()->passe_au_suivant(*p); //Mise à jour de l'élément courant de la particule p.
    }
  }
}
