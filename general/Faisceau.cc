#include "Accelerateur.h"
#include "Faisceau.h"
#include "cases.h"
#include <cmath>
#include <vector>
using namespace std;

//=======================================================================

//Méthode privée

double Faisceau::moyenne_ellipse(ELLIPSE e) const {
  if (nombre_particules() == 0) return 0.0;
  else {
    double moyenne(0.0);
    for (auto& p : particules_) {
      if (p->element_courant() != nullptr) {
        switch (e) {
			case POS_Z:
				{double pos1(p->pos().z());
				moyenne += pos1*pos1;}
				break;
			case VIT_Z:
				{double vit2(p->v().z());
				moyenne += vit2*vit2;}
				break;
			case POS_VIT_Z:
				{double pos3(p->pos().z());
				double vit3(p->v().z());
				moyenne += pos3*vit3;}
				break;
			case POS_R:
				{double pos4(p->element_courant()->coord_orthogonale_position(p));
				moyenne += pos4*pos4;}
				break;
			case VIT_R:
				{double vit5(p->element_courant()->coord_orthogonale_vitesse(p));
				moyenne += vit5*vit5;}
				break;
			case POS_VIT_R:
				{double pos6(p->element_courant()->coord_orthogonale_position(p));
				double vit6(p->element_courant()->coord_orthogonale_vitesse(p));
				moyenne += pos6*vit6;}
				break;
		}
      }
    }
    return (moyenne / nombre_particules());
  }
}

//=======================================================================

//Constructeurs

Faisceau::Faisceau(p_Particule p, bool sens_horaire, double x, unsigned int nombre, const unsigned int lambda, double dl, Accelerateur const& acc, SupportADessin* support_)
	: Dessinable(support_), lambda_(lambda)
{
  unsigned int macro_nombre(nombre/lambda);
  double dx(dl/macro_nombre);

	for (size_t i(0); i<macro_nombre; ++i) {
		particules_.push_back(p_Particule (new Particule(acc, x - 0.5*dl + i*dx, sens_horaire, p->E()*lambda, p->m()*lambda, p->q()*lambda)));
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
			if (not (par==nullptr))par->dessine();
			if (not(par->element_courant()==nullptr))par->element_courant()->dessine();
		}

	} else {sortie << "Le faisceau ne contient pas de particules." << endl;}

	return sortie;
}

//========================================================================

//GETTERS

Collection_P Faisceau::particules() const{return particules_;}

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
  return sqrt(moyenne_ellipse(POS_Z)*moyenne_ellipse(VIT_Z) - moyenne_ellipse(POS_VIT_Z)*moyenne_ellipse(POS_VIT_Z));
}

double Faisceau::emittance_r() const {
  return sqrt(moyenne_ellipse(POS_R)*moyenne_ellipse(VIT_R) - moyenne_ellipse(POS_VIT_R)*moyenne_ellipse(POS_VIT_R));
}


double Faisceau::A_11_r() const {
  return (moyenne_ellipse(VIT_R)/emittance_r());
}

double Faisceau::A_12_r() const {
  return (- moyenne_ellipse(POS_VIT_R)/emittance_r());
}

double Faisceau::A_22_r() const {
  return (moyenne_ellipse(POS_R)/emittance_r());
}

double Faisceau::A_11_z() const {
  return (moyenne_ellipse(VIT_Z)/emittance_z());
}

double Faisceau::A_12_z() const {
  return (- moyenne_ellipse(POS_VIT_Z)/emittance_z());
}
double Faisceau::A_22_z() const {
  return (moyenne_ellipse(POS_Z)/emittance_z());
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
	par->set_support(support_);
	particules_.push_back(par);
}

void Faisceau::initialiser_particules(Accelerateur const& acc, Cases& cases) {
  size_t n((acc.elements()).size());
  for (auto& p : particules_) {
    size_t i(0);
    while(i< n and not acc.elements()[i]->est_dans(*p)) {		//boucle tant que l'element[i] n'est pas l'element courant de p
      ++i;
    }
    if (i < n) {
      p->element_courant(acc.elements()[i]);		//initialise l'element courant de p
      cases.ajouter_p_a_case(p, cases.case_de_abs(acc.pos_en_abs(p)));	//ajoute p dans la case qui associee a la particule p qui depend de l'abscisse curviligne de p dans l'acclerateur (voir cases.cc)
    }
  }
}

//EVOLUTION
void Faisceau::evolue(Accelerateur const& acc, Cases& cases, double dt) {
  size_t i(0);
  while(i<nombre_particules()) {
    if (not particules_[i]->est_sortie()) { //vérifie si la particule est toujours dans l'accélérateur
      particules_[i]->supprimer_forces();

      particules_[i]->ajouter_f_magn((particules_[i]->element_courant())->B(*particules_[i]),dt); //On ajoute à la particule p le champ magnétique produit par l'élément dans lequel elle se trouve.

      size_t j(particules_[i]->case_courante());

      //Ajouter les forces inter-particulaires au moyen de la technique d'optimisation des plus proches voisins
      size_t k(j-1); if (j == 0) k = cases.nombre();
      for (auto const& p : cases.case_num(k)) particules_[i]->ajouter_force_inter_particulaire(*p);
      for (auto const& p : cases.case_num(j)) {
        if (p != particules_[i]) {
          particules_[i]->ajouter_force_inter_particulaire(*p);
        }
      }
      for (auto const& p : cases.case_num(j+1)) particules_[i]->ajouter_force_inter_particulaire(*p);
      //fin de l'ajout des forces initialiser_particulaires

      particules_[i]->bouger(dt); //On modifie la position et la vitesse de la particule en fonction de la force quis s'exerce dessus.


      particules_[i]->element_courant()->passe_au_suivant(*particules_[i]); //Mise à jour de l'élément courant de la particule p.

      if (not particules_[i]->est_sortie()) {
        if (cases.case_de_abs(acc.pos_en_abs(particules_[i])) != j) {
          cases.supprimer_p_de_case(particules_[i],j);		//on supprime la particule de la case dans le cas ou la particule est sortie de celle-ci
          cases.ajouter_p_a_case(particules_[i],j+1);
        }
      }

      ++i;
  } else {
		supprimer_par(i);
	}
  }
}
