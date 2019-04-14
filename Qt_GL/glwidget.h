#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QOpenGLWidget>        // Classe pour faire une fenêtre OpenGL
#include <QTime>            // Classe pour gérer le temps
#include "vue_opengl.h"
#include "Accelerateur.h"

class GLWidget : public QOpenGLWidget
{
public:
  GLWidget(QWidget* parent = nullptr, Accelerateur* a=nullptr)
    : QOpenGLWidget(parent)
    , vitesse_temps(1.0), acc_(a) 
    {acc_->set_support(&vue);}
  virtual ~GLWidget() {}

	// Methodes qui construit l'accelerateur
  void ajouter_mailleFODO(Vecteur3D const& entree, Vecteur3D const& sortie);
  void ajouter_dipole(Vecteur3D const& entree, Vecteur3D const& sortie);
  void ajouter_structure_P10();
  void souder_accelerateur();
  void initialiser_particules();
  void ajouter_faisceau(p_Faisceau const&);

private:
  // Les 3 méthodes clés de la classe QOpenGLWidget à réimplémenter
  virtual void initializeGL()                  override;
  virtual void resizeGL(int width, int height) override;
  virtual void paintGL()                       override;

  // Méthodes de gestion d'évènements
  virtual void keyPressEvent(QKeyEvent* event) override;
  virtual void mousePressEvent(QMouseEvent* event) override;
  virtual void mouseMoveEvent(QMouseEvent* event)  override;
  virtual void timerEvent(QTimerEvent* event)  override;

  // Méthodes de gestion interne
  void pause();

  // Vue : ce qu'il faut donner au contenu pour qu'il puisse se dessiner sur la vue
  VueOpenGL vue;

  // Timer
  int timerId;
  // pour faire évoluer les objets avec le bon "dt"
  QTime chronometre;
  double vitesse_temps;

  // objets à dessiner, faire évoluer
  Accelerateur* acc_;
  
  //Position de la souris
  QPoint lastMousePosition;
};

#endif // GLWIDGET_H
