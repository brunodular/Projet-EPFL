#include "vue_texte.h"
#include "Accelerateur.h"
#include <iomanip>
#include <fstream>
#include <vector>
#include <map>
#include <iterator>
using namespace std;

int main() {
	ofstream sortie("TESTS/exerciceP13/data.txt", ios::out);
	if (not (sortie.fail())) {
		constexpr double dt=2e-10;
		try {
			sortie << setw(MARGE) << "Nombre de cotes" << " | " <<  setw(7) << "Rayon" << " | Nombre d'iterations" << endl;
			for (size_t i(3); i<=11; ++i) {  
				for (double k(1.2); k<=4; k+=0.1) {
					sortie << setw(MARGE) << i << " | " << setw(7) << k << " | ";
					Accelerateur acc(new VueTexte(sortie));
					acc.construire_polygone(i, k);
					acc.souder_accelerateur();
					acc.ajouter_faisceau(p_Particule (new Particule(Vecteur3D(0, 0, 0), Vecteur3D(0,-1,0), 2, 0.938272, e)), true, 0.05, 20, 1, 0.2);
					acc.initialiser_particules();
					size_t j(0);
					while(not acc.encore_des_particules()) {
						acc.evolue(dt);
						++j;
					}
					sortie << j << endl;
				}
			}
		}
		catch (Erreur err) {
			cerr << err.message<< endl;
		}
	}
	sortie.close();
	
	return 0;
}
