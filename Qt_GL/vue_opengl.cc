#include "vue_opengl.h"
#include "vertex_shader.h"
#include "Accelerateur.h"
#include <cmath>

// ======================================================================
/*METHODES DESSINER DE LA SOUS-CLASSE VueOpenGL*/

void VueOpenGL::dessine(Dipole const& el) {
  dessineTore(el.centre(),el.pos_e(),el.pos_s(),el.r_section(),0.27,0.86,1.0);
};

void VueOpenGL::dessine(Particule const& p) {
	QMatrix4x4 matrice;

	matrice.translate((p.pos()).x(), (p.pos()).y(), (p.pos()).z());
	matrice.scale(0.02);

	dessineSphere(matrice, 1.0, 1.0, 1e+12*p.F().norme());
};

void VueOpenGL::dessine(Accelerateur const& acc) {
  for (auto const& e : acc.elements()) e->dessine();
  for (auto const& f : acc.faisceaux()) f->dessine();
}

void VueOpenGL::dessine(SectionDroite const& el) {
  dessineCylindre(el.pos_e(),el.pos_s(),el.r_section(),1.0,0.56,0.27);
}

void VueOpenGL::dessine(Quadrupole const& el) {
  dessineCylindre(el.pos_e(),el.pos_s(),el.r_section(),0.27,0.86,1.0);
}

void VueOpenGL::dessine(MailleFODO const& ma) {
  //1er quadrupole
  dessineCylindre(ma.pos_e(),ma.pos_e_sect_1(),ma.r_section(),0.27,0.86,1.0);
  //1ere section droite
  dessineCylindre(ma.pos_e_sect_1(),ma.pos_e_quad_2(),ma.r_section(),1.0,0.56,0.27);
  //second quadrupole
  dessineCylindre(ma.pos_e_quad_2(),ma.pos_e_sect_2(),ma.r_section(),0.27,0.86,1.0);
  //seconde section droite
  dessineCylindre(ma.pos_e_sect_2(),ma.pos_s(),ma.r_section(),1.0,0.56,0.27);
}

void VueOpenGL::dessine(Faisceau const& f) {
	for (auto const& p : f.particules()) p->dessine();
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
  //glEnable(GL_DEPTH_TEST);
  //glEnable(GL_CULL_FACE);

  sphere.initialize();
  initializePosition();
}

// ======================================================================
void VueOpenGL::initializePosition()
{
  // position initiale
  matrice_vue.setToIdentity();
  matrice_vue.translate(0.0, 0.0, -5.0);
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
  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  sphere.draw(prog, SommetId);                           // dessine la sphère
}

void VueOpenGL::dessineCylindre(Vecteur3D const& base, Vecteur3D const& end, double r, double rouge, double vert, double bleu) {
  QMatrix4x4 matrice;

  const double stacks_length_2(2 * stacks_length);

  const int slices(ceil(2*M_PI*r/slices_height));
  const int stacks(ceil((end-base).norme()/stacks_length_2));
  const double k(2*M_PI/slices);

  Vecteur3D u = ~(end-base);
  Vecteur3D v = r*~(u.orthogonal());
  Vecteur3D w = u^v;

  prog.setUniformValue("vue_modele", matrice_vue * matrice);
  prog.setAttributeValue(CouleurId, 1.0, 1.0, 0.0);
  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  prog.setAttributeValue(CouleurId, rouge, vert, bleu);

  for (int j(0); j < stacks; ++j) {
    for (int i(0); i <= slices; ++i) {
      glBegin(GL_QUAD_STRIP);
      Vecteur3D P(base + j*stacks_length_2*u + cos(i*k)*v + sin(i*k)*w);
      Vecteur3D Q(base + (j+1)*stacks_length_2*u + cos(i*k)*v + sin(i*k)*w);

      glVertex3d(P.x(),P.y(),P.z());
      glVertex3d(Q.x(),Q.y(),Q.z());
    }
  }

  glEnd();
}

void VueOpenGL::dessineTore(Vecteur3D const& centre, Vecteur3D const& base, Vecteur3D const& end, double minor_radius, double rouge, double vert, double bleu) {

  double slices_height_2(slices_height/2);

  const double major_radius((centre-base).norme());
  const double proportion(1/M_PI*asin((base-end).norme()/(2*major_radius)));

  const double a(slices_height_2/minor_radius);
  const double b(1/(proportion*major_radius/stacks_length));

  const int stacks(ceil(2*M_PI*major_radius*proportion/stacks_length));
  const int slices(ceil(2*M_PI*minor_radius/slices_height_2));

  //construction d'une base orthonormale placée au centre du tore
  Vecteur3D u = ~(centre - base);
  Vecteur3D v = ~(centre - end);
  if ((u^v).norme2() == 0) v = u ^ e3;
  else v = ~(v - (u*v)*u);
  Vecteur3D w = u ^ v;

  prog.setUniformValue("vue_modele", matrice_vue);
  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

  for (int i(0); i < slices; ++i) {
    glBegin(GL_QUAD_STRIP);
    prog.setAttributeValue(CouleurId, rouge, vert, bleu);
    for (int j(0); j <= ceil(proportion*stacks); ++j) { // <= pour recouvrir
      for (int k(1); k >= 0; --k) {
        double s((i+k) % slices + 0.5);
        double t(j % stacks + stacks/2);

        double x((major_radius + minor_radius * cos(s*a)) * cos(t*b));
        double y((major_radius + minor_radius * cos(s*a)) * sin(t*b));
        double z(minor_radius * sin(s*a));
        Vecteur3D P(centre + x*u + y*v + z*w);
        glVertex3d(P.x(),P.y(),P.z());
      }
    }
    glEnd();
  }
}

void VueOpenGL::dessineEllipse (double A_11, double A_12, double A_22, double emittance) {
  QMatrix4x4 matrice;
  prog.setUniformValue("vue_modele", matrice);              // On met la matrice identité dans vue_modele

  /* Dessine le cadre blanc */
  matrice.setToIdentity();
  matrice.ortho(-1.0, 1.0, -1.0, 1.0, -10.0, 10.0);         // matrice simple pour faire le cadre
  prog.setUniformValue("projection", matrice);

  prog.setAttributeValue(CouleurId, 1.0, 1.0, 1.0);
  glBegin(GL_LINE_LOOP);                                    // la primitive LINE_LOOP referme le tracé avec une ligne (n lignes)
  prog.setAttributeValue(SommetId, -1.0, -1.0, 2.0);        // le 2.0 dans la composante z permet de mettre le cadre par dessus tout
  prog.setAttributeValue(SommetId, +1.0, -1.0, 2.0);        // ceci fonctionne grace à l'option GL_DEPTH_TEST
  prog.setAttributeValue(SommetId, +1.0, +1.0, 2.0);
  prog.setAttributeValue(SommetId, -1.0, +1.0, 2.0);
  glEnd();

  /* Change de matrice de projection adpatée aux zoom du graph */
  matrice.setToIdentity();
  double xmin(-5.0);
  double xmax(+5.0);
  double ymin(-5.0);
  double ymax(+5.0);
  matrice.ortho(xmin, xmax, ymin, ymax, -10.0, 10.0);
  prog.setUniformValue("projection", matrice);

  /* Dessine les axes */
  prog.setAttributeValue(CouleurId, 0.0, 0.0, 1.0);
  glBegin(GL_LINES);                                        // la primitive LINES dessine une ligne par paire de points (n/2 lignes)
  prog.setAttributeValue(SommetId, xmin, 0.0, -1.0);        // le -1.0 dans la composante z met les axes en arrière plan
  prog.setAttributeValue(SommetId, xmax, 0.0, -1.0);
  prog.setAttributeValue(SommetId, 0.0, ymin, -1.0);
  prog.setAttributeValue(SommetId, 0.0, ymax, -1.0);
  glEnd();


  prog.setAttributeValue(CouleurId, 0.0, 1.0, 0.0);
  glBegin(GL_LINE_STRIP);
  double xpas((xmax-xmin)/120.0);
  for (double x(xmin); x<=xmax; x+=xpas) {
    double y = (-2*A_12*x+std::sqrt((4*(A_12*A_12-A_22*(A_11*x*x-emittance)))))/(2*A_22)*1e-7;
    //std::cout << '(' << x << ", " << y << ')' <<  std::endl;
    prog.setAttributeValue(SommetId, x, y, 0.0);
  }
  for (double x(xmin); x<=xmax; x+=xpas) {
    double y = (-2*A_12*x-std::sqrt((4*(A_12*A_12-A_22*(A_11*x*x-emittance)))))/(2*A_22)*1e-7;
    //std::cout << '(' << x << ", " << y << ')' <<  std::endl;
    prog.setAttributeValue(SommetId, x, y, 0.0);
  }
  glEnd();

}
