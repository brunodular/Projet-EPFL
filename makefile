CXX = g++
CC = $(CXX)
CXXFLAGS = -std=c++11 -Wall -Wuninitialized     #pour identifier les variables non initialisees
CXXFLAGS += -pedantic -Wall
CXXFLAGS += -g                #pour debugger
CXXFLAGS += -pg               #pour profiler
CXXFLAGS += -O2               #pour optimiser la vitesse

all:: testVecteur3D

testVecteur3D: Vecteur3D.o testVecteur3D.o constantes.o
Vecteur3D.o: Vecteur3D.cc Vecteur3D.h constantes.h
constantes.o: constantes.cc constantes.h
testVecteur3D.o: testVecteur3D.cc Vecteur3D.h
