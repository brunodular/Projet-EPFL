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

	public:

		//Constructeur + Destructeur
		Faisceau (p_Particule p,  unsigned int taille, const unsigned int lambda);

		~Faisceau ();

		//Methodes
		void affiche(std::ostream&) const;

		//GETTERS
		double E_moyenne() const;	//renvoie énergie moyenne
		double emittance_h() const;	//renvoie émittance
    double emittance_v() const;
		double A_11() const;	//renvoie un des coefficients des ellipses de phases
		double A_12() const;	//de meme	//On a choisi d'implementer ces caracteristiques d'un faisceaux comme des methodes car celles-ci sont  est
		double A_22() const;	//de meme
		unsigned int nombre_p() const;	//renvoie le nombre de particules


		//EVOLUTION
		void evolue(double dt);

		//DESSINER
		//virtual void dessine() override { support->dessine(*this); }

};
