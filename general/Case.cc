#include "Case.h"
#include "Accelerateur.h"
#include <iomanip>

using namespace std;

//=======================================================================

//CONSTRUCTEUR

Case::Case(Abs abs_e, Abs abs_s, Accelerateur* const& acc) 
	: abs_e_(abs_e), abs_s_(abs_s)
	{if (acc!=nullptr) {pos_e_=acc->abs_en_pos(abs_e_);
		pos_s_=acc->abs_en_pos(abs_s_);}
	}
	
Case::~Case () {
	for (auto const& p : particules_) {
		delete p;
	}
	particules_.clear();
	delete case_suiv_; case_suiv_=nullptr;
	delete case_preced_; case_preced_=nullptr;
}

//METHODE

bool Case::passe_au_suivant(Particule& p) const {
	if (prod_mixte(e3,pos_e_,pos_s_) > 0) {
		p.case_courante(case_suiv_);
		return true;
	} else if (prod_mixte(e3,p.pos(), pos_e_)<0) {
		p.case_courante(case_preced_);
		return true;
	} else {
		return false;
	}
}

//GETTERS

Abs Case::abs_e() const {return abs_e_;}
Abs Case::abs_s() const {return abs_s_;}
Vecteur3D Case::pos_e() const {return pos_e_;}
Vecteur3D Case::pos_s() const {return pos_s_;}
Collection_P Case::particules() const {
	 return particules_;
}


//SETTERS

void Case::case_suiv(Case* suiv) {
	case_suiv_=suiv;
}

void Case::case_preced(Case* preced) {
	case_preced_ = preced;
}

void Case::ajouter_par(Particule* const& p) {
	particules_.push_back(p);
}

//AFFICHE

ostream& Case::affiche(ostream& sortie) const {
	sortie<<setw(MARGE)<<"Position d'entrée : "<<pos_e_<< endl << setw(MARGE)<< "Position de sortie : "<<pos_s_ << endl;
	if (!particules_.empty()) {
		for (auto const& p : particules_) {
			support_->dessine(*p);
		}
	}
}
