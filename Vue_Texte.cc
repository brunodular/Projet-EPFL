#include "Vue_Texte.h"

//=======================================================================
void Vue_Texte::dessine(Dipole const& d) {
	d.affiche(flot_);
}

void Vue_Texte::dessine(Particule const& p) {
	p.affiche(flot_);
}

void Vue_Texte::dessine(Accelerateur const& acc) {
	acc.affiche(flot_);
}

void Vue_Texte::dessine(ElementCourbe const& elc) {
	elc.affiche(flot_);
}

void Vue_Texte::dessine(SectionDroite const& sd) {
	sd.affiche(flot_);
}

void Vue_Texte::dessine(Element const& el) {
	el.affiche(flot_);
}

void Vue_Texte::dessine(ElementDroit const& el) {
  el.affiche(flot_);
}

void Vue_Texte::dessine(Quadrupole const& el) {
  el.affiche(flot_);
}

/*
void Vue_Texte::dessine(Faisceau const& f) {
	f.affiche(flot_);
}*/
