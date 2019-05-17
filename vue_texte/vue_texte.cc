#include "vue_texte.h"

//=======================================================================
void VueTexte::dessine(Dipole const& d) {
	d.affiche(flot_);
}

void VueTexte::dessine(Particule const& p) {
	p.affiche(flot_);
}

void VueTexte::dessine(Accelerateur const& acc) {
	acc.affiche(flot_);
}

void VueTexte::dessine(ElementCourbe const& elc) {
	elc.affiche(flot_);
}

void VueTexte::dessine(SectionDroite const& sd) {
	sd.affiche(flot_);
}

void VueTexte::dessine(Element const& el) {
	el.affiche(flot_);
}

void VueTexte::dessine(ElementDroit const& el) {
  el.affiche(flot_);
}

void VueTexte::dessine(Quadrupole const& el) {
  el.affiche(flot_);
}

void VueTexte::dessine(Faisceau const& f) {
	f.affiche(flot_);
}

void VueTexte::dessine(MailleFODO const& m) {
  m.affiche(flot_);
}
