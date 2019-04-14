#include <QApplication>
#include "glwidget.h"
#include <iostream>
using namespace std;

int main(int argc, char* argv[])
{
	try{
	QApplication a(argc, argv);
  
    Accelerateur CERN(nullptr);    
    GLWidget w(nullptr, &CERN);
	
	w.ajouter_structure_P10();		//construit la structure de l'exercice P10
    
    w.souder_accelerateur();
    
    Faisceau f(p_Particule (new Particule(Vecteur3D(3.01, 0, 0), Vecteur3D(0, -1, 0), 2, 0.938272, e)), 1000, 10);
    
    w.ajouter_faisceau(new Faisceau(f));
	
	w.initialiser_particules();
  
	w.show();
  
	return a.exec(); }
	catch (Erreur err){cout<<err.message<<endl;}
}
