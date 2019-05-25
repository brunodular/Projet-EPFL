#include <QKeyEvent>
#include <QTimerEvent>
#include <QMatrix4x4>
#include <iostream>
#include "glwidget.h"
using namespace std;

//=======================================================================
void GLWidget::mousePressEvent(QMouseEvent* event)
{
  lastMousePosition = event->pos();
}

//=======================================================================
void GLWidget::mouseMoveEvent(QMouseEvent* event)
{
  /* If mouse tracking is disabled (the default), the widget only receives
   * mouse move events when at least one mouse button is pressed while the
   * mouse is being moved.
   *
   * Pour activer le "mouse tracking" if faut lancer setMouseTracking(true)
   * par exemple dans le constructeur de cette classe.
   */

  if (event->buttons() & Qt::LeftButton) {
	constexpr double petit_angle(.4); // en degrés

	// Récupère le mouvement relatif par rapport à la dernière position de la souris
	QPointF d = event->pos() - lastMousePosition;
	lastMousePosition = event->pos();

	vue.rotate(petit_angle * d.manhattanLength(), d.y(), d.x(), 0);

	update();
  }
}

// ======================================================================
void GLWidget::initializeGL()
{
  vue.init();
  timerId = startTimer(20);
}

// ======================================================================
void GLWidget::resizeGL(int width, int height)
{
  /* On commance par dire sur quelle partie de la
   * fenêtre OpenGL doit dessiner.
   * Ici on lui demande de dessiner sur toute la fenêtre.
   */
  glViewport(0, 0, width, height);

  /* Puis on modifie la matrice de projection du shader.
   * Pour ce faire on crée une matrice identité (constructeur
   * par défaut), on la multiplie par la droite par une matrice
   * de perspective.
   * Plus de détail sur cette matrice
   *     http://www.songho.ca/opengl/gl_projectionmatrix.html
   * Puis on upload la matrice sur le shader à l'aide de la
   * méthode de la classe VueOpenGL
   */
  QMatrix4x4 matrice;
  matrice.perspective(70.0, qreal(width) / qreal(height ? height : 1.0), 1e-3, 1e5);
  vue.setProjection(matrice);
}

// ======================================================================
void GLWidget::paintGL()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  if (numero_ == 0) acc_->dessine();
  else vue.dessineEllipse(acc_->A_11_r(numero_-1), acc_->A_12_r(numero_-1), acc_->A_22_r(numero_-1), acc_->emittance_r(numero_-1)); //vue.dessineSinus(acc_->emittance_r()*1e+8);
}


// ======================================================================
void GLWidget::keyPressEvent(QKeyEvent* event)
{
  constexpr double petit_angle(5.0); // en degrés
  constexpr double petit_pas(0.25);

  switch (event->key()) {

  case Qt::Key_Left:
    vue.rotate(petit_angle, 0.0, -1.0, 0.0);
    break;

  case Qt::Key_Right:
    vue.rotate(petit_angle, 0.0, +1.0, 0.0);
    break;

  case Qt::Key_Up:
    vue.rotate(petit_angle, -1.0, 0.0, 0.0);
    break;

  case Qt::Key_Down:
    vue.rotate(petit_angle, +1.0, 0.0, 0.0);
    break;

  case Qt::Key_PageUp:
  case Qt::Key_W:
    vue.translate(0.0, 0.0,  petit_pas);
    break;

  case Qt::Key_PageDown:
  case Qt::Key_S:
    vue.translate(0.0, 0.0, -petit_pas);
    break;

  case Qt::Key_A:
    vue.translate( petit_pas, 0.0, 0.0);
    break;

  case Qt::Key_D:
    vue.translate(-petit_pas, 0.0, 0.0);
    break;

  case Qt::Key_R:
    vue.translate(0.0, -petit_pas, 0.0);
    break;

  case Qt::Key_F:
    vue.translate(0.0,  petit_pas, 0.0);
    break;

  case Qt::Key_Q:
    vue.rotate(petit_angle, 0.0, 0.0, -1.0);
    break;

  case Qt::Key_E:
    vue.rotate(petit_angle, 0.0, 0.0, +1.0);
    break;

  case Qt::Key_Home:
    vue.initializePosition();
    break;

  case Qt::Key_Space:
    pause();
    if (toucheEspace) {acc_->affiche_info_ellipse(std::cout);
      toucheEspace=false;
    } else {toucheEspace=true;}
    break;

  case Qt::Key_P:
    evo_par_affichage *= 2;
    break;

  case Qt::Key_O:
    if (evo_par_affichage > 1) evo_par_affichage /= 2;
    break;
  };

  update(); // redessine
}

// ======================================================================
void GLWidget::timerEvent(QTimerEvent* event)
{
  Q_UNUSED(event);

  //double dt = 1e-10;
  double dt = chronometre.restart() * 1e-12;

  if (numero_ == 0) {
    for (size_t i(0); i<evo_par_affichage; ++i) {
      acc_->evolue(dt);
    }
  }

  update();
}

// ======================================================================
void GLWidget::pause()
{
  if (numero_ > 0) return;
  if (timerId == 0) {
	// dans ce cas le timer ne tourne pas alors on le lance
	timerId = startTimer(20);
	chronometre.restart();
  } else {
	// le timer tourne alors on l'arrête
	killTimer(timerId);
	timerId = 0;
  }
}


//METHODES POUR CONSTRUIRE ACCELERATEUR

void GLWidget::ajouter_structure_P10() {
	acc_->construire_structure_P10();
  acc_->souder_accelerateur();
}

void GLWidget::construire_polygone(size_t n, double R) {
  acc_->construire_polygone(n,R);
}

void GLWidget::ajouter_faisceau(p_Particule p, bool sens_horaire, double x, unsigned int nombre, const unsigned int lambda, double dl, bool distribution_normale) {
	acc_->ajouter_faisceau(p, sens_horaire, x, nombre, lambda, dl, distribution_normale);
	acc_->initialiser_particules();
}

//Interface utilisateur

unsigned int demande_uint(string const& question, unsigned int min) {
  cout << question << " ( ≥ " << min << " ) ";
  unsigned int n;
  do {
    cin >> n;
  } while (n<min);
  return n;
}

double demande_double(string const& question, double min) {
  cout << question << " ( ≥ " << min << " ) ";
  double x;
  do {
    cin >> x;
  } while (x<min);
  return x;
}

bool demande(string const& question) {
  cout << question << " o pour OUI, n pour NON ";
  char c(' ');
  do {
    cin >> c;
  } while (c != 'o' and c != 'n');
  return (c == 'o');
}


void GLWidget::construire_polygone() {
  construire_polygone(demande_uint("Nombre de côtés :",3),demande_double("Rayon de l'accélérateur :",1));
}

void GLWidget::ajouter_faisceau(vector<unique_ptr<GLWidget>>& v) {
  bool sens_horaire(demande("Sens horaire ?"));
  double q(0.0);
  if (sens_horaire) q=e;
  else q=-e;
  ajouter_faisceau(new Particule(Vecteur3D(0, 0, 0), Vecteur3D(0,-1,0), 2, 0.938272, q),sens_horaire, demande_double("Faisceau centré en :",0.0), demande_uint("Nombre de particules :",1), demande_uint("Facteur de macro-particules :",1),demande_double("Etendue du faisceau :",0.05),demande("Distribution normale (OUI) ou linéaire (NON) :"));

  v.push_back(unique_ptr<GLWidget>(new GLWidget(nullptr, acc(), v.size() + 1)));
}

void GLWidget::bienvenue(vector<unique_ptr<GLWidget>>& v) {
  cout << "Bienvenue dans ce simulateur d'accélérateur de particules !" << endl;
  cout << "Pour commencer, construisons un accélérateur." << endl;
  construire_polygone();
  while (demande("Ajouter un faisceau de particules ?")) {
    ajouter_faisceau(v);
  }
}
