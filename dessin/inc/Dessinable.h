#pragma once

#include "Support_a_dessin.h"

class Dessinable {
public:
  Dessinable(SupportADessin* support = nullptr);
  virtual ~Dessinable() {}
  virtual void dessine() = 0;

protected:
  SupportADessin* support;
};
