#pragma once
#include <iostream>
#include "Element.h"
#include "Faisceau.h"

class Accelerateur : public Dessinable {
	private:
		Collection_F faisceaux_;		//Pointeurs pour le polymorphisme et c'est moins risque d'utliser des unique_ptr lors d'oubli
		Collection_E elements_;
		double longueur_;
		Cases cases_;

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
		Collection_F faisceaux() const;

		//Methodes
			//Afficher
		std::ostream& affiche(std::ostream&) const;
		std::ostream& affiche_part(std::ostream&) const;

			//Ajouter

		//ces méthodes affectent le support de l'Accélérateur aux supports des particules et éléments ajoutés.
		void ajouter_faisceau(p_Particule p, double x, unsigned int nombre, const unsigned int lambda, double dl);
		void ajouter_el(p_Element const&);
		void ajouter_faisceau_par(size_t i, p_Particule const&);

    //MEGA-Constructeurs
    void construire_polygone(size_t n, double R);
    void construire_structure_P10();
    void ajouter_mailleFODO(Vecteur3D const& entree, Vecteur3D const& sortie);

		//CONSTRUIRE
		void souder_accelerateur(); //Cette méthode soude tous les éléments entre eux en settant l'élément suivant/précédent de chaque élément comme pointeur vers l'élément qui le suit/précède dans le vecteur elements_. Cette méthode suppose que les élément ont étés ajoutés dans l'ordre attendu.


    //Abscisse curviligne
    Vecteur3D abs_en_pos(double x) const;
    Abs pos_en_abs(p_Particule const&) const;

		void initialiser_particules(); //Initialise les élément_courant_ des Particules

			//Supprimer
		void supprimer_faisceau(size_t i);

		void supprimer_faisceau();
		void supprimer_el();

		void supprimer_faisceau_par(size_t i);
		void supprimer_faisceau_par(size_t i, size_t j);

		//EVOLUTION
		void evolue(double dt);

		//DESSINER
		virtual void dessine() override { if(support_!=nullptr) support_->dessine(*this); }
		virtual void dessine_faisceau() const;
		virtual void dessine_element() const;
		virtual void set_support(SupportADessin*) override;

};

//Operateur externe

std::ostream& operator<<(std::ostream&, Accelerateur const&);
