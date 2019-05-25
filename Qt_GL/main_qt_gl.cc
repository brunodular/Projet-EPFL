#include <QApplication>
#include "glwidget.h"
#include <iostream>
#include <memory>
using namespace std;

int main(int argc, char* argv[])
{
	try{
  	QApplication a(argc, argv);

    GLWidget w(nullptr, new Accelerateur (nullptr));

    vector<unique_ptr<GLWidget>> affichage_ellipses;

    w.bienvenue(affichage_ellipses);

    for (auto& h : affichage_ellipses) h->show();
    w.show();

  	return a.exec();
  } catch (Erreur err){cout << err.message << endl;}
}
