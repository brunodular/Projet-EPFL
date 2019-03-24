#include "Dessinable.h"
#include "Particule.h"

class Faisceau:public Dessinable {
	private:
		Particule* particule_typique_;	//Particule typique de reference
		unsigned int nb_p_; 			//nombre de particules dans le faisceau
		const unsigned int lambda_;
		
	public:
		
		//Constructeur + Destructeur
		Faisceau (Particule* p, unsigned int nb, unsigned int l);
		
		~Faisceau () {delete particule_typique_; particule_typique_=nullptr;}
		
		//Methodes
		void affiche(std::ostream&) const;
		
		//GETTERS
		double E_moyenne() const;	
		double emittance() const;
		double A_11() const;
		double A_12() const;		//On a choisi d'implementer ces caracteristiques d'un faisceaux comme des methodes car celles-ci sont  est 
		double A_22() const;
		
		//EVOLUTION
		void evolue(double dt);
		
		//DESSINER
		virtual void dessine() override { support->dessine(*this); }
	
};
