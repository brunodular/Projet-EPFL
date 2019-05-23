#pragma once

#include <vector>
#include <unordered_set>
#include "Particule.h"

typedef std::unordered_set<p_Particule> Set_P;

class Cases {
private:
  std::vector<Set_P> cases_; //cf. fichier conception pour voir une explication
  const double eps_; //proportion de la longueur d'une case par rapport à la longueur totale (entre 0 et 1)
  const uint nombre_; //nombre d'ensemble de pointeurs vers des particules (nombre de "case")

public:
  //Constructeur + destructeur
  Cases(uint nombre);
  ~Cases();
  Cases(Cases const&) = delete; //dans notre conception une case ne peut pas etre copiee
  Cases& operator=(Cases const&) = delete;

	//Methodes
  void ajouter_p_a_case(p_Particule const& p, size_t i);
  void supprimer_p_de_case(p_Particule const& p, size_t i);
  bool p_est_dans_case(p_Particule const& p, size_t i) const; //renvoie vrai si la particule est dans la case, faux sinon
  size_t case_de_abs(double abs) const; //renvoie le numéro de la case contenant une particule d'abscisse curviligne abs donnée


  //Getters
  uint nombre() const;
  Set_P& case_num(size_t i); //renvoie la "case" d'indice i
};
