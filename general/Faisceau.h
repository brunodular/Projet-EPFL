#pragma once

#include "Dessinable.h"
#include "Particule.h"
#include <vector>
#include <memory>
#include "Element.h"

typedef Particule* p_Particule;
typedef Element* p_Element;

typedef std::vector<p_Particule> Collection_P;

//=======================================================================

class Faisceau : public Dessinable {
	private:
		p_Particule particule_typique_;
		unsigned int lambda_;
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
		Faisceau (p_Particule p, double x, unsigned int nombre, const unsigned int lambda, double dl, Accelerateur const& acc, SupportADessin* support_=nullptr); //x et dl sont des abscisses curvilignes, donc entre 0 et 1

		Faisceau(SupportADessin* support_);

		Faisceau () = default;

		~Faisceau () = default;

		Faisceau (Faisceau const&);

		Faisceau& operator=(Faisceau const&) = default;

		//Methodes
		std::ostream& affiche(std::ostream&) const;
		std::ostream& affiche_part(std::ostream&) const;
		virtual void set_support(SupportADessin*) override;

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
		void initialiser_particules(p_Element const&);

		//DESSINER
		virtual void dessine() override { support_->dessine(*this); }
		virtual void dessine_particule() const;

		//EVOLUTION
		void evolue(double);
};
