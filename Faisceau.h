#include "Dessinable.h"
#include "Particule.h"
#include <vector>

typedef Particule* p_Particule;

typedef std::vector<p_Particule> Collection_P;

//=======================================================================

class Faisceau:public Dessinable {
	private:
		p_Particule particule_typique_;	//Particule typique de reference
		const unsigned int lambda_;
		Collection_P particules_;

    //méthodes privées, utilisées dans les autres méthodes
      //paramètres radiaux
    double moyenne_pos_2_r() const;
    double moyenne_vit_2_r() const;
    double moyenne_pos_vit_r() const;

      //paramètres verticaux
    double moyenne_pos_2_z() const;
    double moyenne_vit_2_z() const;
    double moyenne_pos_vit_z() const;

	public:

		//Constructeur + Destructeur
		Faisceau (p_Particule p,  unsigned int taille, const unsigned int lambda);

		~Faisceau ();

		//Methodes
		void affiche(std::ostream&) const;

		//GETTERS
		double E_moyenne() const;	//renvoie énergie moyenne

		double emittance_r() const;
    double emittance_z() const;

		double A_11_r() const;
		double A_12_r() const;
		double A_22_r() const;

    double A_11_z() const;
		double A_12_z() const;
		double A_22_z() const;

		unsigned int nombre_particules() const;	//renvoie le nombre de particules

    //modifier particules
    void supprimer_par(size_t i);

		//DESSINER
		virtual void dessine() override { support->dessine(*this); }
};
