#include "vue_opengl.h"
#include "vertex_shader.h" // Identifiants Qt de nos différents attributs
#include "Accelerateur.h"
#include <cmath>

constexpr double DEUXPI=2*M_PI;

// ======================================================================
/*METHODES DESSINER DE LA SOUS-CLASSE VueOpenGL*/

/*
void VueOpenGL::dessine(Contenu const& a_dessiner)
{
   // Dessine le 1er cube (à l'origine)
  dessineCube();

  QMatrix4x4 matrice;
  // Dessine le 2e cube
  matrice.translate(0.0, 1.5, 0.0);
  matrice.scale(0.25);
  dessineCube(matrice);
  dessineAxes(matrice);

  // Dessine le 3e cube
  matrice.setToIdentity();
  matrice.translate(0.0, 0.0, 1.5);
  matrice.scale(0.25);
  matrice.rotate(45.0, 0.0, 1.0, 0.0);
  dessineCube(matrice);

  // Dessine le 4e cube
  matrice.setToIdentity();
  matrice.rotate(a_dessiner.infos(), 0.0, 5.0, 0.0);
  matrice.translate(0.0, 2.3, 0.0);
  matrice.rotate(a_dessiner.infos(), 1.0, 0.0, 0.0);
  matrice.scale(0.2);
  dessineCube(matrice);
}

*/
				//------------------------------
void VueOpenGL::dessine(Dipole const& d) {



};

				//------------------------------

void VueOpenGL::dessine(Particule const& p) {
	QMatrix4x4 matrice;

	matrice.translate((p.pos()).x(), (p.pos()).y(), (p.pos()).z());
	matrice.scale(0.05);

	//dessineAxes(matrice, true);
	dessineSphere(matrice, 1.0, 1.0 ,0.0);
};

				//-----------------------------
void VueOpenGL::dessine(Accelerateur const& acc) {
	QMatrix4x4 matrice;
	dessineTore(matrice);
}

				//----------------------------
void VueOpenGL::dessine(ElementCourbe const& elc) {

}

				//----------------------------
void VueOpenGL::dessine(SectionDroite const& sd) {

}

				//----------------------------
void VueOpenGL::dessine(Element const& el) {

}

				//---------------------------
void VueOpenGL::dessine(ElementDroit const& eld) {

}

				//---------------------------
void VueOpenGL::dessine(Quadrupole const& qd) {


}

				//---------------------------

void VueOpenGL::dessine(Faisceau const& f) {


}


//=======================================================================
void VueOpenGL::dessineAxes (QMatrix4x4 const& point_de_vue, bool en_couleur)
{
  prog.setUniformValue("vue_modele", matrice_vue * point_de_vue);

  glBegin(GL_LINES);

  // axe X
  if (en_couleur) {
    prog.setAttributeValue(CouleurId, 1.0, 0.0, 0.0); // rouge
  } else {
    prog.setAttributeValue(CouleurId, 1.0, 1.0, 1.0); // blanc
  }
  prog.setAttributeValue(SommetId, 0.0, 0.0, 0.0);
  prog.setAttributeValue(SommetId, 1.0, 0.0, 0.0);

  // axe Y
  if (en_couleur) prog.setAttributeValue(CouleurId, 0.0, 1.0, 0.0); // vert
  prog.setAttributeValue(SommetId, 0.0, 0.0, 0.0);
  prog.setAttributeValue(SommetId, 0.0, 1.0, 0.0);

  // axe Z
  if (en_couleur) prog.setAttributeValue(CouleurId, 0.0, 0.0, 1.0); // bleu
  prog.setAttributeValue(SommetId, 0.0, 0.0, 0.0);
  prog.setAttributeValue(SommetId, 0.0, 0.0, 1.0);

  glEnd();
}


// ======================================================================
void VueOpenGL::init()
{
  /* Initialise notre vue OpenGL.
   * Dans cet exemple, nous créons et activons notre shader.
   *
   * En raison du contenu des fichiers *.glsl, le shader de cet exemple
   * NE permet QUE de dessiner des primitives colorées
   * (pas de textures, brouillard, reflets de la lumière ou autres).
   *
   * Il est séparé en deux parties VERTEX et FRAGMENT.
   * Le VERTEX :
   * - récupère pour chaque sommet des primitives de couleur (dans
   *     l'attribut couleur) et de position (dans l'attribut sommet)
   * - multiplie l'attribut sommet par les matrices 'vue_modele' et
   *     'projection' et donne le résultat à OpenGL
   *   - passe la couleur au shader FRAGMENT.
   *
   * Le FRAGMENT :
   *   - applique la couleur qu'on lui donne
   */

  prog.addShaderFromSourceFile(QOpenGLShader::Vertex,   ":/vertex_shader.glsl");
  prog.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/fragment_shader.glsl");

  /* Identifie les deux attributs du shader de cet exemple
   * (voir vertex_shader.glsl).
   *
   * L'attribut identifié par 0 est particulier, il permet d'envoyer un
   * nouveau "point" à OpenGL
   *
   * C'est pourquoi il devra obligatoirement être spécifié et en dernier
   * (après la couleur dans cet exemple, voir plus bas).
   */

  prog.bindAttributeLocation("sommet",  SommetId);
  prog.bindAttributeLocation("couleur", CouleurId);

  // Compilation du shader OpenGL
  prog.link();

  // Activation du shader
  prog.bind();

  /* Activation du "Test de profondeur" et du "Back-face culling"
   * Le Test de profondeur permet de dessiner un objet à l'arrière-plan
   * partielement caché par d'autres objets.
   *
   * Le Back-face culling consiste à ne dessiner que les face avec ordre
   * de déclaration dans le sens trigonométrique.
   */
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_CULL_FACE);

  sphere.initialize();
  initializePosition();
}

// ======================================================================
void VueOpenGL::initializePosition()
{
  // position initiale
  matrice_vue.setToIdentity();
  matrice_vue.translate(0.0, 0.0, -4.0);
  matrice_vue.rotate(60.0, 0.0, 1.0, 0.0);
  matrice_vue.rotate(45.0, 0.0, 0.0, 1.0);
}

// ======================================================================
void VueOpenGL::translate(double x, double y, double z)
{
  QMatrix4x4 translation_supplementaire;
  translation_supplementaire.translate(x, y, z);
  matrice_vue = translation_supplementaire * matrice_vue;
}

// ======================================================================
void VueOpenGL::rotate(double angle, double dir_x, double dir_y, double dir_z)
{
  // Multiplie la matrice de vue par LA GAUCHE
  QMatrix4x4 rotation_supplementaire;
  rotation_supplementaire.rotate(angle, dir_x, dir_y, dir_z);
  matrice_vue = rotation_supplementaire * matrice_vue;
}

// ======================================================================
void VueOpenGL::dessineCube (QMatrix4x4 const& point_de_vue)
{
  prog.setUniformValue("vue_modele", matrice_vue * point_de_vue);

  glBegin(GL_QUADS);
  // face coté X = +1
  prog.setAttributeValue(CouleurId, 1.0, 0.0, 0.0); // rouge
  prog.setAttributeValue(SommetId, +1.0, -1.0, -1.0);
  prog.setAttributeValue(SommetId, +1.0, +1.0, -1.0);
  prog.setAttributeValue(SommetId, +1.0, +1.0, +1.0);
  prog.setAttributeValue(SommetId, +1.0, -1.0, +1.0);

  // face coté X = -1
  prog.setAttributeValue(CouleurId, 0.0, 1.0, 0.0); // vert
  prog.setAttributeValue(SommetId, -1.0, -1.0, -1.0);
  prog.setAttributeValue(SommetId, -1.0, -1.0, +1.0);
  prog.setAttributeValue(SommetId, -1.0, +1.0, +1.0);
  prog.setAttributeValue(SommetId, -1.0, +1.0, -1.0);

  // face coté Y = +1
  prog.setAttributeValue(CouleurId, 0.0, 0.0, 1.0); // bleu
  prog.setAttributeValue(SommetId, -1.0, +1.0, -1.0);
  prog.setAttributeValue(SommetId, -1.0, +1.0, +1.0);
  prog.setAttributeValue(SommetId, +1.0, +1.0, +1.0);
  prog.setAttributeValue(SommetId, +1.0, +1.0, -1.0);

  // face coté Y = -1
  prog.setAttributeValue(CouleurId, 0.0, 1.0, 1.0); // cyan
  prog.setAttributeValue(SommetId, -1.0, -1.0, -1.0);
  prog.setAttributeValue(SommetId, +1.0, -1.0, -1.0);
  prog.setAttributeValue(SommetId, +1.0, -1.0, +1.0);
  prog.setAttributeValue(SommetId, -1.0, -1.0, +1.0);

  // face coté Z = +1
  prog.setAttributeValue(CouleurId, 1.0, 1.0, 0.0); // jaune
  prog.setAttributeValue(SommetId, -1.0, -1.0, +1.0);
  prog.setAttributeValue(SommetId, +1.0, -1.0, +1.0);
  prog.setAttributeValue(SommetId, +1.0, +1.0, +1.0);
  prog.setAttributeValue(SommetId, -1.0, +1.0, +1.0);

  // face coté Z = -1
  prog.setAttributeValue(CouleurId, 1.0, 0.0, 1.0); // magenta
  prog.setAttributeValue(SommetId, -1.0, -1.0, -1.0);
  prog.setAttributeValue(SommetId, -1.0, +1.0, -1.0);
  prog.setAttributeValue(SommetId, +1.0, +1.0, -1.0);
  prog.setAttributeValue(SommetId, +1.0, -1.0, -1.0);

  glEnd();
}

//=======================================================================

void VueOpenGL::dessineSphere (QMatrix4x4 const& point_de_vue,
                               double rouge, double vert, double bleu)
{
  prog.setUniformValue("vue_modele", matrice_vue * point_de_vue);
  prog.setAttributeValue(CouleurId, rouge, vert, bleu);  // met la couleur
  sphere.draw(prog, SommetId);                           // dessine la sphère
}


//=======================================================================

void VueOpenGL::dessineTore (QMatrix4x4 const& point_de_vue, uint numc, uint numt,
								double rouge, double vert, double bleu)
{
	prog.setAttributeValue(CouleurId, 1.0, 1.0, 1.0);
	prog.setAttributeValue(SommetId, 0.0, 0.0, 0.0);
	for (int i = 0; i < numc; i++) {
		glBegin(GL_QUAD_STRIP);
		for (int j = 0; j <= numt; j++) {
			for (int k = 1; k >= 0; k--) {
				double s = (i + k) % numc + 0.5;
				double t = j % numt;
		
				double x = (1 + 0.1 * cos(s * DEUXPI / numc)) * cos(t * DEUXPI / numt);
				double y = (1 + 0.1 * cos(s * DEUXPI / numc)) * sin(t * DEUXPI / numt);
				double z = 0.1 * sin(s * DEUXPI/ numc);
                glVertex3d(2 * x, 2 * y, 2 * z);
            }
        }
        glEnd();
    }
}
