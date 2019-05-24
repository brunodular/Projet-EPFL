#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QOpenGLWidget>        // Classe pour faire une fenêtre OpenGL
#include <QTime>            // Classe pour gérer le temps
#include "vue_opengl.h"
#include "Accelerateur.h"

class GLWidget : public QOpenGLWidget
{
public:
  GLWidget(QWidget* parent = nullptr, Accelerateur* a=nullptr, bool autreFenetre=false)
    : QOpenGLWidget(parent)
    , evo_par_affichage(1), acc_(a), autreFenetre_(autreFenetre)
    {if(!autreFenetre) acc_->set_support(&vue);}
  
  Accelerateur* acc() const {return acc_;}

	// Methodes qui construit l'accelerateur
  void ajouter_structure_P10();
  void ajouter_faisceau(p_Particule p, bool sens_horaire, double x, unsigned int nombre, const unsigned int lambda, double dl);
  void construire_polygone(size_t n, double R);

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
  unsigned int evo_par_affichage; //nombre d'évolutions par affichage

  // objets à dessiner, faire évoluer
  Accelerateur* acc_;

  //Position de la souris
  QPoint lastMousePosition;
  
  //Indique si a appuye sur space precedemment
  bool toucheEspace=true;
  
  //Indique si repose sur un autre GLWidget
  bool autreFenetre_;
};

#endif // GLWIDGET_H
