#include "Vue_Texte.h"
#include "Accelerateur.h"
using namespace std;

int main() {
	constexpr double dt=1e-11;
	try {
		Accelerateur acc(new VueTexte(cout));
		acc.construire_polygone(7, 3.2);
		acc.souder_accelerateur();
		acc.ajouter_faisceau(p_Particule (new Particule(Vecteur3D(0, 0, 0), Vecteur3D(0,-1,0), 2, 0.938272, e)), 0.01, 10, 1, 0.05);
		acc.initialiser_particules();
		size_t i(0);
		acc.dessine();
		while(not acc.faisceaux().empty()) {
			cout << i << endl;
			acc.evolue(dt);
			acc.affiche_part(cout);
			++i;
		}
	}
	catch (Erreur err) {
		cout << err.message<< endl;
	}

	return 0;
}
