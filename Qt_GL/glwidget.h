#pragma once

#include <QOpenGLWidget>        // Classe pour faire une fenêtre OpenGL
#include <QTime>            // Classe pour gérer le temps
#include "vue_opengl.h"
#include "Accelerateur.h"
#include <string>
#include <memory>
#include <vector>

class GLWidget : public QOpenGLWidget
{
public:
  GLWidget(QWidget* parent = nullptr, Accelerateur* a = nullptr, size_t num = 0)
    : QOpenGLWidget(parent)
    , evo_par_affichage(1), acc_(a), numero_(num)
    {if(num == 0) acc_->set_support(&vue);}

  Accelerateur* acc() const {return acc_;}

	// Methodes qui construit l'accelerateur
  void ajouter_structure_P10();
  void ajouter_faisceau(p_Particule p, bool sens_horaire, double x, unsigned int nombre, const unsigned int lambda, double dl, bool distribution_normale = false);
  void construire_polygone(size_t n, double R);

  void construire_polygone();
  void ajouter_faisceau(std::vector<std::unique_ptr<GLWidget>>&);
  void bienvenue(std::vector<std::unique_ptr<GLWidget>>&);

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
  size_t numero_; //numéro du faisceau associé. 0 si fenêtre principale
};

//Interface utilisateur

unsigned int demande_uint(std::string const& question, unsigned int min);
double demande_double(std::string const& question, double min);
bool demande(std::string const& question);
