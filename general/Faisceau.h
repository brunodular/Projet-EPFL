#pragma once

#include "Dessinable.h"
#include "cases.h"
#include <vector>
#include "Element.h"

//=======================================================================

enum ELLIPSE {POS_Z, VIT_Z, POS_VIT_Z, POS_R, VIT_R, POS_VIT_R};

class Faisceau : public Dessinable {
	private:
		const unsigned int lambda_; 		//coefficient pour determiner le nb de macro-particules voulant etre simulees
		Collection_P particules_;	//(voir constantes.h pour le typedef de Collection_P)

		//méthodes privées, utilisées dans les autres méthodes et notamment dans les methodes pour determiner les coefficients elliptiques
		double moyenne_ellipse(ELLIPSE) const;

	public:

		//Constructeurs + Destructeur
		Faisceau (p_Particule p, bool sens_horaire, double x, unsigned int nombre, const unsigned int lambda, double dl, Accelerateur const& acc, SupportADessin* support_=nullptr); //x et dl sont des abscisses curvilignes, donc entre 0 et 1

		Faisceau () = default;

		~Faisceau () = default;

		Faisceau (Faisceau const&) = delete; //nous avons decide de d'enlever la copie de faisceau car ceci ne fait aucun sens physiquement

		Faisceau& operator=(Faisceau const&) = delete;

		//Methodes
		std::ostream& affiche(std::ostream&) const;
		std::ostream& affiche_part(std::ostream&) const;		//affiche seulement les informations sur les particules du faisceau
		virtual void set_support(SupportADessin*) override;		//initialise le support a dessin de chaque particule du faisceau

		//GETTERS
		Collection_P particules() const;

		double E_moyenne() const;	//renvoie énergie moyenne

		double emittance_r() const;
		double emittance_z() const;

		double A_11_r() const;
		double A_12_r() const;		//renvoie les coefficients elliptiques demandees selon les coordonnees orthogonales
		double A_22_r() const;

		double A_11_z() const;
		double A_12_z() const;		//renvoie selon les coordonnees verticales
		double A_22_z() const;

		unsigned int nombre_particules() const;	//renvoie le nombre de macro-particules
		unsigned int nombre_particules_simulees() const; //renvoie le nombre de particules hypothétique

		//Modifier la collection de particules
		void supprimer_par(size_t i);		//supprime i-eme particules du faisceau
		void supprimer_par();
		void ajouter_par(p_Particule const&);
		void initialiser_particules(Accelerateur const& acc, Cases& cases); 	//methode qui initialise les elements courants et les cases courantes de chaque particule du faisceau

		//DESSINER
		virtual void dessine() override { support_->dessine(*this); }

		//EVOLUTION
		void evolue(Accelerateur const&, Cases&, double);
};
