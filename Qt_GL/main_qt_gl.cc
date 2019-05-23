#include <QApplication>
#include "glwidget.h"
#include <iostream>
using namespace std;

int main(int argc, char* argv[])
{
	try{
  	QApplication a(argc, argv);

    GLWidget w(nullptr, new Accelerateur (nullptr));

    w.construire_polygone(11,2.5);

  	//w.ajouter_structure_P10();		//construit la structure de l'exercice P10

    w.ajouter_faisceau(p_Particule (new Particule(Vecteur3D(0, 0, 0), Vecteur3D(0,-1,0), 2, 0.938272, e)), true, 0.1, 100, 10, 0.5);

  	w.show();

  	return a.exec();
  } catch (Erreur err){cout<<err.message<<endl;}
}
