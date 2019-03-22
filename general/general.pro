TEMPLATE = lib

CONFIG = staticlib -std=c++11

QMAKE_CXX = g++ -std=c++11

INCLUDEPATH = ../dessin

SOURCES += Vecteur3D.cc Particule.cc Element.cc Accelerateur.cc constantes.cc

HEADERS += Vecteur3D.h Particule.h Element.h Ahelerateur.h constantes.h ../dessin/Dessinable.h ../dessin/Support_a_dessin.h
