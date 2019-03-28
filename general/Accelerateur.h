#pragma once
#include <vector>
#include <iostream>
#include "Element.h"
#include "Dessinable.h"
#include "Faisceau.h"

typedef Particule* p_Particule;	//On a choisi de mettre des pointeurs afin d'optimiser la simulation et puis dans la cas ou l'on voudrait cree dans sous-classes de Particule afin d'utiliser le polymorphisme
typedef Element* p_Element;		//On a choisi de mettre des pointeurs a la C a la place de unique_ptr car les elements sont pointe par d'autres pointeurs (pointeur sur l'element courant et suivant par les Particules et les Elements respectivement cf. definition de la classe Element et Particule)

typedef std::vector<p_Particule> Collection_P;		//pour faciliter la comprehension du code et pour que ce soit plus clair
typedef std::vector<p_Element> Collection_E;

class Accelerateur : public Dessinable {
	private:
		Collection_P particules_;		//Pointeurs pour le polymorphisme et c'est moins risque d'utliser des unique_ptr lors d'oubli
		Collection_E elements_;

	public:
		//Constructeurs
		Accelerateur (Collection_P const&, Collection_E const&, SupportADessin* support); //pas besoin de mettre les vector par defaut car les vectors sont automatiquement initialisés au vector vide

		Accelerateur(SupportADessin* support);

		Accelerateur (Accelerateur const&)=delete;
		Accelerateur& operator=(Accelerateur)=delete;

		//Destructeur

		~Accelerateur () {
			for (auto el : elements_) {
				delete el;
			}
			elements_.clear();
			for (auto par : particules_) {
				delete par;
			}
			particules_.clear();
		}

		//Methodes
			//Afficher
		std::ostream& affiche(std::ostream&) const;
    std::ostream& affiche_part(std::ostream&) const;

			//Ajouter

    //ces méthodes affectent le support de l'Accélérateur aux supports des particules et éléments ajoutés.
		void ajouter_par(p_Particule const&);
		void ajouter_el(p_Element const&);

      //CONSTRUIRE
    void souder_accelerateur(); //Cette méthode soude tous les éléments entre eux en settant l'élément suivant el_suiv_ de chaque élément comme pointeur vers l'élément qui le suit dans le vecteur elements_. Cette méthode suppose que les élément ont étés ajoutés dans l'ordre attendu.

    void initialiser_particules(); //Initialise les élément_courant_ des Particules

			//Supprimer
		void supprimer_par(size_t i);

		void supprimer_par();
		void supprimer_el();

		//EVOLUTION
		void evolue(double dt);

		//DESSINER
		virtual void dessine() override { support->dessine(*this); }
};

//Operateur externe

std::ostream& operator<<(std::ostream&, Accelerateur const&);
