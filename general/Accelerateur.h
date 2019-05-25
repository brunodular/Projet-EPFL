#pragma once

#include <iostream>
#include "Element.h"
#include "Faisceau.h"

class Accelerateur : public Dessinable {
	private:
		Collection_F faisceaux_; //Pointeurs pour le polymorphisme
		Collection_E elements_;
		double longueur_; //longueur de l'accelerateur
		Cases cases_; //cases pour l'optimisation des meilleurs voisins

		//Methodes privees
		void ajouter_mailleFODO(Vecteur3D const& entree, Vecteur3D const& sortie); //methode qui ajoute une MailleFODO utilisee dans les "mega-constructeurs" de l'accelerateur

		PositionEtElement abs_element (double x) const; //renvoie un size_t indiquant l'indice de l'element tel que l'abscisse curviligne x correspond a un vecteur dans cet element, et retourne x soustrait par les longueurs des elements precedents

	public:
		//Constructeurs
		Accelerateur (Collection_F const&, Collection_E const&, SupportADessin* support); //pas besoin de mettre les vector par defaut car les vectors sont automatiquement initialisés au vector vide
		Accelerateur(SupportADessin* support);

		Accelerateur (Accelerateur const&)=delete;
		Accelerateur& operator=(Accelerateur)=delete;

		//Destructeur

		~Accelerateur ();

		//Getters
		Collection_E elements() const;
    double r_section() const;
		Collection_F faisceaux() const;

    double emittance_r(size_t i = 0) const;
		double emittance_z(size_t i = 0) const;

		double A_11_r(size_t i = 0) const;
		double A_12_r(size_t i = 0) const;		//renvoie les coefficients elliptiques demandees selon les coordonnees orthogonales
		double A_22_r(size_t i = 0) const;

    double moyenne_ellipse(ELLIPSE, size_t i = 0) const;

		//Methodes
			//Afficher
		std::ostream& affiche(std::ostream&) const;
		std::ostream& affiche_part(std::ostream&) const;
    std::ostream& affiche_info_ellipse(std::ostream&) const;

			//Ajouter

		//ces méthodes affectent le support de l'Accélérateur aux supports des particules et éléments ajoutés.
		void ajouter_faisceau(p_Particule p, bool sens_horaire, double x, unsigned int nombre, const unsigned int lambda, double dl, bool distribution_normale = false);
		void ajouter_el(p_Element const&);
		void ajouter_faisceau_par(size_t i, p_Particule const&);

		bool encore_des_particules() const; //renvoie vrai s'il y a encore des particules dans l'accelerateur, faux sinon

		//MEGA-Constructeurs
		void construire_polygone(size_t n, double R); //methode qui fait en sorte que l'accelerateur est de la forme d'un polygone regulier de n cotes et avec un cercle de circonference de rayon R
		void construire_structure_P10(); //methode qui initialise les elements afin d'obtenir la forme presentee dans la serie P10

		//CONSTRUIRE
		void souder_accelerateur(); //Cette méthode soude tous les éléments entre eux en settant l'élément suivant/précédent de chaque élément comme pointeur vers l'élément qui le suit/précède dans le vecteur elements_. Cette méthode suppose que les élément ont étés ajoutés dans l'ordre attendu.

		//Abscisse curviligne
		Vecteur3D abs_en_pos(double x) const; //methode qui prend une abscisse curviligne (entre 0 et 1) et renvoie une position en fonction de la geometrie de l'accelerateur
		Abs pos_en_abs(p_Particule const&) const; //methode qui renvoie l'abscissse curviligne d'une particule dans l'accelerateur
		Vecteur3D tangente_en_abs(double x, bool sens_horaire) const; //methode qui revoie un Vecteur3D dans la direction de la trajectoire ideale et dans le sens donne en parametre
    Vecteur3D abs_en_pos(double x, double y, double z) const; //méthode qui renvoie la position correspondant à l'abscisse curviligne x, et de position (y,z) dans le plan perpendiculaire à l'accelerateur en ce point. Permet de creer des faisceaux avec une distribution normale dans les trois dimensions.

		void initialiser_particules(); //Initialise les élément_courant_ et les cases courantes des particules des faisceaux

			//Supprimer
		void supprimer_faisceau(size_t i); //permet de supprimer le i-eme faisceau de l'accelerateur

		void supprimer_faisceau();
		void supprimer_el();

		void supprimer_faisceau_par(size_t i); //supprime les particules du i-eme faisceau
		void supprimer_faisceau_par(size_t i, size_t j); //supprimer la j-eme particule du i-eme faisceau

		//EVOLUTION
		void evolue(double dt);

		//DESSINER
		virtual void dessine() override { if(support_!=nullptr) support_->dessine(*this); }

		virtual void set_support(SupportADessin*) override;

};

//Operateur externe

std::ostream& operator<<(std::ostream&, Accelerateur const&);
