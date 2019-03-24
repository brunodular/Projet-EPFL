#include "Dessinable.h"
#include "Particule.h"
#include <vector>

typedef Particule* p_Particule;

typedef vector<p_Particule> Collection_P;

//=======================================================================

class Faisceau:public Dessinable {
	private:
		p_Particule particule_typique_;	//Particule typique de reference
		const unsigned int lambda_;		//Ou alors le mettre comme static ou comme une constante dans le fichier constante?
		Collection_P particules_;
		
	public:
		
		//Constructeur + Destructeur
		Faisceau (p_Particule p, Collection_P const& par, const unsigned int lambda);
		
		~Faisceau () {delete particule_typique_; 
			particule_typique_=nullptr;
			for (auto par : particules_) {
				delete par;
			}
			particules_.clear();
		}
		
		//Methodes
		void affiche(std::ostream&) const;
		
		//GETTERS
		double E_moyenne() const;	//renvoie énergie moyenne
		double emittance() const;	//renvoie émittance
		double A_11() const;	//renvoie un des coefficients des ellipses de phases
		double A_12() const;	//de meme	//On a choisi d'implementer ces caracteristiques d'un faisceaux comme des methodes car celles-ci sont  est 
		double A_22() const;	//de meme
		unsigned int nombre_p() const;	//renvoie le nombre de particules
		
		
		//EVOLUTION
		void evolue(double dt);
		
		//DESSINER
		virtual void dessine() override { support->dessine(*this); }
	
};
