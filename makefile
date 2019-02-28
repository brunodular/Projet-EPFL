CXX = g++
CC = $(CXX)
CXXFLAGS = -std=c++11

all:: testVecteur
constantes.o: constantes.cc constantes.h
Vecteur3D.o: Vecteur3D.cc Vecteur3D.h constantes.h
testVecteur.o: testVecteur.cc Vecteur3D.h
testVecteur: Vecteur3D.o testVecteur.o constantes.o
