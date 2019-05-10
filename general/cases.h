#pragma once

#include <vector>
#include <set>
#include "Particule.h"

typedef std::set<p_Particule> Set_P;

class Cases {
private:
  std::vector<Set_P> cases_;
  const double eps_; //proportion de la longueur d'une case par rapport à la longueur totale (entre 0 et 1)
  const uint nombre_;

public:
  Cases(uint nombre);
  ~Cases();
  Cases(Cases const&) = delete;
  Cases& operator=(Cases const&) = delete;

  void ajouter_p_a_case(p_Particule const& p, size_t i);
  void supprimer_p_de_case(p_Particule const& p, size_t i);
  bool p_est_dans_case(p_Particule const& p, size_t i) const;
  Set_P& case_num(size_t i);
  uint nombre() const;

  size_t case_de_abs(double abs) const; //renvoie le numéro de la case contenant une particule d'abscisse curviligne abs donnée
};
