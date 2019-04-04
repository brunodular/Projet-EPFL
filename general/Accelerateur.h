#pragma once
#include <vector>
#include <iostream>
#include <memory>
#include "Element.h"
#include "Dessinable.h"
#include "Faisceau.h"

typedef Particule* p_Particule;	//On a choisi de mettre des pointeurs afin d'optimiser la simulation et puis dans la cas ou l'on voudrait cree dans sous-classes de Particule afin d'utiliser le polymorphisme
typedef Element* p_Element;		//On a choisi de mettre des pointeurs a la C a la place de unique_ptr car les elements sont pointe par d'autres pointeurs (pointeur sur l'element courant et suivant par les Particules et les Elements respectivement cf. definition de la classe Element et Particule)
typedef Faisceau* p_Faisceau;		//pour faciliter la comprehension du code et pour que ce soit plus clair

typedef std::vector<p_Element> Collection_E;
typedef std::vector<p_Faisceau> Collection_F;

class Accelerateur : public Dessinable {
	private:
		Collection_F faisceaux_;		//Pointeurs pour le polymorphisme et c'est moins risque d'utliser des unique_ptr lors d'oubli
		Collection_E elements_;

	public:
		//Constructeurs
		Accelerateur (Collection_F const&, Collection_E const&, SupportADessin* support); //pas besoin de mettre les vector par defaut car les vectors sont automatiquement initialisés au vector vide

		Accelerateur(SupportADessin* support);

		Accelerateur (Accelerateur const&)=delete;
		Accelerateur& operator=(Accelerateur)=delete;

		//Destructeur

		~Accelerateur () {
			for (auto el : elements_) {
				delete el;
			}
			elements_.clear();
			for (auto f : faisceaux_) {
				delete f;
			}
			faisceaux_.clear();
		}

		//Methodes
			//Afficher
		std::ostream& affiche(std::ostream&) const;
		std::ostream& affiche_part(std::ostream&) const;

			//Ajouter

		//ces méthodes affectent le support de l'Accélérateur aux supports des particules et éléments ajoutés.
		void ajouter_faisceau(p_Faisceau const&);
		void ajouter_el(p_Element const&);
		void ajouter_faisceau_par(size_t i, p_Particule const&);

		//CONSTRUIRE
		void souder_accelerateur(); //Cette méthode soude tous les éléments entre eux en settant l'élément suivant el_suiv_ de chaque élément comme pointeur vers l'élément qui le suit dans le vecteur elements_. Cette méthode suppose que les élément ont étés ajoutés dans l'ordre attendu.

		void initialiser_particules(); //Initialise les élément_courant_ des Particules

			//Supprimer
		void supprimer_faisceau(size_t i);

		void supprimer_faisceau();
		void supprimer_el();
		
		void supprimer_faisceau_par(size_t i);
		void supprimer_faisceau_par(size_t i, size_t j);

		//EVOLUTION
		void evolue(double dt);
		void evoluetest(double dt) {};

		//DESSINER
		virtual void dessine() override { support->dessine(*this); }
		virtual void dessine_faisceau() const;
		virtual void dessine_element() const;
};

//Operateur externe

std::ostream& operator<<(std::ostream&, Accelerateur const&);
