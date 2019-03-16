CXX = g++
CC = $(CXX)
CXXFLAGS = -std=c++11 -Wall -Wuninitialized     #pour identifier les variables non initialisees
CXXFLAGS += -pedantic -Wall
#CXXFLAGS += -g                #pour debugger
#CXXFLAGS += -pg               #pour profiler
#CXXFLAGS += -O2               #pour optimiser la vitesse

all:: testVecteur3D testParticule testElement

testVecteur3D: Vecteur3D.o testVecteur3D.o constantes.o
testParticule: Vecteur3D.o constantes.o Particule.o testParticule.o

Vecteur3D.o: Vecteur3D.cc Vecteur3D.h constantes.h
constantes.o: constantes.cc constantes.h
Particule.o: Particule.cc Particule.h Vecteur3D.h constantes.h
Element.o: Element.cc Element.h Particule.h

testVecteur3D.o: testVecteur3D.cc Vecteur3D.h
testParticule.o: testParticule.cc Particule.h
testElement.o: testElement.cc Element.h
