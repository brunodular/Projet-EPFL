#include "cases.h"
#include "cmath"
using namespace std;

Cases::Cases(uint nombre) : cases_(vector<Set_P> (nombre)), eps_(1 / nombre), nombre_(nombre) {}

Cases::~Cases() {
	for (auto& cas : cases_) {
		for (auto& p : cas) {
			delete p;
		}
		cas.clear();
	}
	cases_.clear();
}

void Cases::ajouter_p_a_case(p_Particule const& p, size_t i) {
  if (i == cases_.size()) i = 0;
  cases_[i].insert(p);
}

void Cases::supprimer_p_de_case(p_Particule const& p, size_t i) {
  if (i == cases_.size()) i = 0;
  cases_[i].erase(p);
}

bool Cases::p_est_dans_case(p_Particule const& p, size_t i) const {
  if (i == cases_.size()) i = 0;
  if (cases_[i].find(p) != cases_[i].cend()) return true;
  else return false;
}

size_t Cases::case_de_abs(double abs) const {
  return floor(abs/eps_);
}

Set_P& Cases::case_num(size_t i) {
  if (i == cases_.size()) i = 0;
  return cases_[i];
}

uint Cases::nombre() const {return nombre_;}
