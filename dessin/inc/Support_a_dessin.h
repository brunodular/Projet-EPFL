#ifndef SUPPORT_A_DESSIN_H
#define SUPPORT_A_DESSIN_H

class Dipole;
class Element;
class Particule;
class Accelerateur;
class ElementCourbe;
class SectionDroite;

class SupportADessin
{
 public:
  virtual ~SupportADessin()=default;

  virtual void dessine(Dipole const&) = 0;
  virtual void dessine(Particule const&) = 0;			
  virtual void dessine(Accelerateur const&) = 0;
  virtual void dessine(ElementCourbe const&) = 0;
  virtual void dessine(SectionDroite const&) = 0;
  virtual void dessine(Element const&) = 0;
  
  SupportADessin () = default;
  
 private:
  SupportADessin(SupportADessin const&)=delete;
  SupportADessin& operator=(SupportADessin const&)=delete;
};

#endif

