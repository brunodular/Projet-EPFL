#include "Case.h"
#include "Accelerateur.h"
#include <iomanip>

using namespace std;

//=======================================================================

Case::Case(Abs abs_e, Abs abs_s, Accelerateur const& acc) 
	: pos_e_(acc.abs_en_pos(abs_e)), pos_s_(acc.abs_en_pos(abs_s))
	{}
	
Case::~Case () {
	for (auto const& p : particules_) {
		delete p;
	}
	particules_.clear();
	delete case_suiv_; case_suiv_=nullptr;
	delete case_preced_; case_preced_=nullptr;
}


bool Case::passe_au_suivant(Particule& p) const {
	if (prod_mixte(e3,p.pos(),pos_s_) > 0) {
		p.case_courante(case_suiv_);
		return true;
	} else if (prod_mixte(e3,p.pos(), pos_e_)<0) {
		p.case_courante(case_preced_);
		return true;
	} else {
		return false;
	}
	
}

void Case::case_suiv(Case* suiv) {
	case_suiv_=suiv;
}

void Case::case_preced(Case* preced) {
	case_preced_ = preced;
}

void Case::ajouter_par(Particule* const& p) {
	particules_.push_back(p);
}

Collection_P Case::particules() const {
	 return particules_;
}

ostream& Case::affiche(ostream& sortie) const {
	sortie<<setw(MARGE)<<"Position d'entrée : "<<pos_e_<< endl << setw(MARGE)<< "Position de sortie : "<<pos_s_ << endl;
	if (!particules_.empty()) {
		for (auto const& p : particules_) {
			support_->dessine(*p);
		}
	}
}
