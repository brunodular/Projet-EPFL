#include <vector>
#include <iostream>
#include "Element.h"

typedef Particule* p_Particule;
typedef Element* p_Element;

typedef std::vector<p_Particule> Collection_P;		//pour faciliter la comprehension du code et pour que ce soit plus clair
typedef std::vector<p_Element> Collection_E;

class Accelerateur {
	private:
		Collection_P particules_;		//Pointeurs pour le polymorphisme et c'est moins risque d'utliser des unique_ptr lors d'oubli
		Collection_E elements_;
	
	public:
		//Constructeurs
		Accelerateur (Collection_P const&, Collection_E const&); //pas besoin de mettre les vector par defaut car les vectors sont automatiquement initialise au vector vide 
		
		Accelerateur()=default;
		
		Accelerateur (Accelerateur const&)=delete;
		Accelerateur& operator=(Accelerateur)=delete;
		
		//Destructeur
		
		~Accelerateur () {}
		
		//Methodes
			//Afficher
		std::ostream& afficher(std::ostream&) const;
		
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
