CXX = g++
CC = $(CXX)
CXXFLAGS = -std=c++11

all:: testVecteur
Vecteur3D.o: Vecteur3D.cc Vecteur3D.h
testVecteur.o: testVecteur.cc Vecteur3D.h
testVecteur: Vecteur3D.o testVecteur.o
