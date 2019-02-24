CXX=g++
CC=$(CXX)
CXXFLAGS=-std=c++11 -Wall
LDLIBS=-lm

all: testVecteur3D

testVecteur3D: Vecteur3D.o testVecteur3D.o

Vecteur3D.o: Vecteur3D.cc Vecteur3D.h
testVecteur3D.o: testVecteur3D.cc Vecteur3D.h
