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

//Constructeur

Faisceau::Faisceau (p_Particule p, unsigned int nombre, const unsigned int lambda)
	: particule_typique_(p), lambda_(lambda)
{}

//Destructeur
Faisceau::~Faisceau () {
  delete particule_typique_;
  particule_typique_=nullptr;
  for (auto& par : particules_) {
    delete par;
  }
  particules_.clear();
}

//Methodes

void Faisceau::affiche(ostream& sortie) const {
	sortie << "Particule typique du faisceau : " << endl;
	particule_typique_->affiche(sortie);
}

//GETTERS

double Faisceau::E_moyenne() const {
	double moyenne(0.0);
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


//modifier particules
void Faisceau::supprimer_par(size_t i) {
  delete particules_[i];
  particules_.erase(particules_.begin() + i);
}
