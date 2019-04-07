#pragma once
class SupportADessin;

class Dessinable {
 public:
  Dessinable(SupportADessin* support=nullptr)
    : support_(support)
  {}
  virtual ~Dessinable() {}
  virtual void dessine() = 0;

  virtual void set_support(SupportADessin* sup) {support_ = sup;}

 protected:
  SupportADessin* support_; //on implémente un pointeur a la place d'une reference si jamais on aurait besoin de copier
};
