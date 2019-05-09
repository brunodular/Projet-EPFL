#ifndef VUEOPENGL_H
#define VUEOPENGL_H

#include <QOpenGLShaderProgram> // Classe qui regroupe les fonctions OpenGL liées aux shaders
#include <QMatrix4x4>
#include "Support_a_dessin.h"
#include "Vecteur3D.h"
#include "Element.h"
#include "glsphere.h"

const double slices_height(0.08);
const double stacks_length(0.025);

class VueOpenGL : public SupportADessin {
 public:
  // méthode(s) de dessin (héritée(s) de SupportADessin)
  virtual void dessine(Dipole const&) override;
  virtual void dessine(Particule const&) override;
  virtual void dessine(Accelerateur const&) override;
  virtual void dessine(ElementCourbe const&) override {}
  virtual void dessine(SectionDroite const&) override;
  virtual void dessine(Element const&) override {}
  virtual void dessine(ElementDroit const&) override {}
  virtual void dessine(Quadrupole const&) override;
  virtual void dessine(Faisceau const&) override;
  virtual void dessine(MailleFODO const&) override;

  // méthodes de (ré-)initialisation
  void init();
  void initializePosition();

  // méthode set
  void setProjection(QMatrix4x4 const& projection)
  { prog.setUniformValue("projection", projection); }

  // Méthodes set
  void translate(double x, double y, double z);
  void rotate(double angle, double dir_x, double dir_y, double dir_z);

  // méthode utilitaire offerte pour simplifier
  void dessineAxes(QMatrix4x4 const& point_de_vue, bool en_couleur = true);
  void dessineCube(QMatrix4x4 const& point_de_vue = QMatrix4x4() );
  void dessineSphere(QMatrix4x4 const& point_de_vue,
                     double rouge = 1.0, double vert = 1.0, double bleu = 1.0);
  void dessineCylindre(Vecteur3D const& base, Vecteur3D const& end, double r,double rouge = 1.0, double vert = 1.0, double bleu = 1.0);
  void dessineTore(Vecteur3D const& centre, Vecteur3D const& base, Vecteur3D const& end, double minor_radius, double rouge = 1.0, double vert = 1.0, double bleu = 1.0);

 private:
  // Un shader OpenGL encapsulé dans une classe Qt
  QOpenGLShaderProgram prog;
  GLSphere sphere;

  // Caméra
  QMatrix4x4 matrice_vue;
};

#endif
