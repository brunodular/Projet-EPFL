#include "Faisceau.h"
#include <cmath>
using namespace std;

//=======================================================================

//méthodes privées, utilisées dans les autres méthodes
  //paramètres verticaux
double moyenne_pos_2_z() const {
  if (nombre_particules == 0) return 0.0;
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
double moyenne_vit_2_z() const {
  if (nombre_particules == 0) return 0.0;
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
double moyenne_pos_vit_z() const {
  if (nombre_particules == 0) return 0.0;
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
double moyenne_pos_2_r() const {
  if (nombre_particules == 0) return 0.0;
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
double moyenne_vit_2_r() const {
  if (nombre_particules == 0) return 0.0;
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
double moyenne_pos_vit_r() const {
  if (nombre_particules == 0) return 0.0;
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
	: particule_typique(Particule* (new Particule (p))), lambda_(lambda)
{}

//Destructeur
Faisceau::~Faisceau () {
  delete particule_typique_;
  for (auto& par : particules_) {
    delete par;
  }
  particules_.clear();
}

//Methodes

void Faisceau::affiche(ostream& sortie) {
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

double Faisceau::emittance_z const {
  return sqrt(moyenne_pos_2_z()*moyenne_vit_2_z() - moyenne_pos_vit_z()*moyenne_pos_vit_z());
}

double Faisceau::emittance_r const {
  return sqrt(moyenne_pos_2_r()*moyenne_vit_2_r() - moyenne_pos_vit_r()*moyenne_pos_vit_r());
}


double Faisceau::A_11() const {

}


double Faisceau::A_12() const {

}


double Faisceau::A_22() const {

}

unsigned int Faisceau::nombre_particules() const {
	return particules_.size();
}

//EVOLUTION

void evolue(double dt) {

}
