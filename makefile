CXX = g++
CC = $(CXX)
CXXFLAGS = -std=c++11 -Wall -Wuninitialized     #pour identifier les variables non initialisees
CXXFLAGS += -pedantic -Wall
#CXXFLAGS += -g                #pour debugger
#CXXFLAGS += -pg               #pour profiler
#CXXFLAGS += -O2               #pour optimiser la vitesse

all:: testVecteur3D testParticule testElement testAccel1

#testVecteur3D: Vecteur3D.o testVecteur3D.o constantes.o
#testParticule: Vecteur3D.o constantes.o Particule.o testParticule.o
testAccel1: Accelerateur.o testAccel1.o Element.o constantes.o Particule.o Vecteur3D.o Vue_Texte.o

Vecteur3D.o: Vecteur3D.cc Vecteur3D.h constantes.h
constantes.o: constantes.cc constantes.h 
Particule.o: Particule.cc Particule.h Vecteur3D.h constantes.h Element.h Dessinable.h
Element.o: Element.cc Element.h Particule.h Dessinable.h
Accelerateur.o: Accelerateur.cc Accelerateur.h Element.h Dessinable.h Support_a_dessin.h
Vue_Texte.o: Vue_Texte.cc Vue_Texte.h Support_a_dessin.h

#testVecteur3D.o: testVecteur3D.cc Vecteur3D.h
#testParticule.o: testParticule.cc Particule.h
#testElement.o: testElement.cc Element.h
testAccel1.o: testAccel1.cc Accelerateur.h Support_a_dessin.h Dessinable.h
