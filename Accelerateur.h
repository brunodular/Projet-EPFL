#include <vector>
#include <memory>
#include <iostream>
#include <string>
#include "Element.h"

typedef std::unique_ptr<Particule> p_Particule;
typedef std::unique_ptr<Element> p_Element;

typedef vector<p_Particule> Collection_P;		//pour faciliter la comprehension du code et pour que ce soit plus clair
typedef vector<p_Element> Collection_E;

class Accelerateur {
	private:
		Collection_P particules_;		//Pointeurs pour le polymorphisme et c'est moins risque d'utliser des unique_ptr lors d'oubli
		Collection_E elements_;
	
	public:
		//Constructeurs
		Accelerateur (Collection_P =, Collection_E =) ;
		
		Accelerateur (Accelerateur const&)=delete;
		Accelerateur& operator=(Accelerateur)=delete;
		
		//Destructeur
		
		//Methodes
			//Afficher
		std::ostream& afficher(std::ostream&) const;
		void afficher_boucle(std::ostream&, string const&, Collection_E const&) const;
		void afficher_boucle(std::ostream&, string const&, Collection_P const&) const;
		
			//Ajouter
		void ajouter_par(p_Particule const&);
		void ajouter_el(p_Element const&);
		
			//Supprimer
		void supprimer_par();
		void supprimer_el();
		
			//Evolution de l'accélérateur
		void evolue();
	
};

//Operateur externe

std::ostream& operator << (std::ostream&, Accelerateur const&);
