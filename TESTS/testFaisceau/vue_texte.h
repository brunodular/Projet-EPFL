#pragma once
#include <iostream>
#include "../general/Support_a_dessin.h"
#include "../general/Accelerateur.h"

class VueTexte : public SupportADessin {
	private:
		std::ostream& flot_;

	public:
		//CONSTRUCTEUR + DESTRUCTEUR
		VueTexte(std::ostream& flot) : flot_(flot) {}

		virtual ~VueTexte() {}

		VueTexte(VueTexte const&) = delete;

		//METHODES DESSINE
		virtual void dessine(Dipole const&) override;
		virtual void dessine(Particule const&) override;
		virtual void dessine(Accelerateur const&) override;
		virtual void dessine(ElementCourbe const&) override;
		virtual void dessine(SectionDroite const&) override;
		virtual void dessine(Element const&) override;
		virtual void dessine(ElementDroit const&) override;
		virtual void dessine(Quadrupole const&) override;
		virtual void dessine(Faisceau const&) override;

};
