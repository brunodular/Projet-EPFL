CXX = g++
CC = $(CXX)
CXXFLAGS = -std=c++11 -Wall -Wuninitialized     #pour identifier les variables non initialisees
CXXFLAGS += -pedantic -Wall
#CXXFLAGS += -g                #pour debugger
#CXXFLAGS += -pg               #pour profiler
#CXXFLAGS += -O2               #pour optimiser la vitesse

all:: testAccel1 exerciceP10 testParticule testVecteur3D

testVecteur3D: Vecteur3D.o testVecteur3D.o constantes.o
testParticule: Vecteur3D.o constantes.o Particule.o testParticule.o Accelerateur.o Dessinable.o Vue_Texte.o
testAccel1: Accelerateur.o testAccel1.o Element.o constantes.o Particule.o Vecteur3D.o Dessinable.o Vue_Texte.o Faisceau.o
exerciceP10: exerciceP10.o Accelerateur.o Element.o constantes.o Particule.o Vecteur3D.o Dessinable.o Vue_Texte.o Faisceau.o

Vecteur3D.o: Vecteur3D.cc Vecteur3D.h constantes.h
constantes.o: constantes.cc constantes.h
Particule.o: Particule.cc Particule.h Vecteur3D.h constantes.h Element.h Dessinable.h
Faisceau.o: Faisceau.cc Faisceau.h Particule.h Dessinable.h
Element.o: Element.cc Element.h Particule.h Dessinable.h
Accelerateur.o: Accelerateur.cc Accelerateur.h Element.h Dessinable.h Support_a_dessin.h
Vue_Texte.o: Vue_Texte.cc Vue_Texte.h Support_a_dessin.h Accelerateur.h Faisceau.h
Dessinable.o: Dessinable.cc Dessinable.h Support_a_dessin.h

testVecteur3D.o: testVecteur3D.cc Vecteur3D.h
testParticule.o: testParticule.cc Particule.h Vue_Texte.h
testAccel1.o: testAccel1.cc Accelerateur.h Vue_Texte.h
exerciceP10.o: exerciceP10.cc Accelerateur.h Vue_Texte.h
