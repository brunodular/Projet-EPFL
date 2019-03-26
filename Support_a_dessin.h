#pragma once

class Dipole;
class Particule;
class Accelerateur;
class Element;
class ElementCourbe;
class ElementDroit;
class SectionDroite;
class Quadrupole;
class Faisceau;

class SupportADessin {
public:
  virtual ~SupportADessin() = default;

  virtual void dessine(Dipole const&) = 0;
  virtual void dessine(Particule const&) = 0;
  virtual void dessine(Accelerateur const&) = 0;
  virtual void dessine(ElementCourbe const&) = 0;
  virtual void dessine(SectionDroite const&) = 0;
  virtual void dessine(Element const&) = 0;
  virtual void dessine(ElementDroit const&) = 0;
  virtual void dessine(Quadrupole const&) = 0;
  //virtual void dessine(Faisceau const&) = 0;

  SupportADessin () = default;

private:
  SupportADessin(SupportADessin const&) = delete;
  SupportADessin& operator=(SupportADessin const&) = delete;
};
