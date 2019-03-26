#include "Accelerateur.h"
#include "Vue_Texte.h"
using namespace std;

int main() {
  constexpr double dt(0.1);

  Vue_Texte* p_Vue (new Vue_Texte(cout));
  Accelerateur CERN(p_Vue);
  CERN.ajouter_par(new Particule(Vecteur3D(1.00984, -0.191837, 0), Vecteur3D(-210200, -2.64754e+08, 0), 2, 0.938272, e, p_Vue));

  CERN.dessine();
  CERN.evolue(dt); //Petit test juste pour voir si la méthode fonctionne. La particule va en fait disparaître dès la première itération de evolue car elle n'est dans aucun élément.

  CERN.dessine();

  return 0;
}
