#include <iostream>
#include "../../general/inc/Accelerateur.h"
#include "../../dessin/inc/Support_a_dessin.h"

class Vue_Texte : public SupportADessin {
	private:
		std::ostream& flot_;

	public:
		//CONSTRUCTEUR + DESTRUCTEUR
		Vue_Texte(std::ostream& flot) : flot_(flot) {}

		virtual ~Vue_Texte() {}

		Vue_Texte(Vue_Texte const&) = delete;

		//METHODES DESSINE
		virtual void dessine(Dipole const&) override;
		virtual void dessine(Particule const&) override;
		virtual void dessine(Accelerateur const&) override;
		virtual void dessine(ElementCourbe const&) override;
    virtual void dessine(ElementDroit const&) override;
		virtual void dessine(SectionDroite const&) override;
		virtual void dessine(Element const&) override;
    virtual void dessine(Quadrupole const&) override;

};
