#pragma once
class SupportADessin;

class Dessinable {
 public:
  Dessinable(SupportADessin* support=nullptr)
    : support(support)
  {}
  virtual ~Dessinable() {}
  virtual void dessine() = 0;

  virtual void set_support(SupportADessin* sup) {support = sup;}

 protected:
  SupportADessin* support; //on implémente un pointeur a la place d'une reference si jamais on aurait besoin de copier
};
