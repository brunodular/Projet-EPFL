CXX = g++
CC = $(CXX)
CXXFLAGS = -std=c++11 -Wall -Wuninitialized     #pour identifier les variables non initialisees
CXXFLAGS += -pedantic -Wall -ffreestanding
CXXFLAGS += -g                #pour debugger
CXXFLAGS += -pg               #pour profiler
CXXFLAGS += -O2               #pour optimiser la vitesse

all:: tests/src/testAccel1

#testVecteur3D: Vecteur3D.o testVecteur3D.o constantes.o
#testParticule: Vecteur3D.o constantes.o Particule.o testParticule.o
testAccel1: obj/testAccel1.o obj/Accelerateur.o obj/Element.o obj/constantes.o obj/Particule.o obj/Vecteur3D.o obj/Vue_Texte.o obj/Dessinable.o

obj/Vecteur3D.o: general/src/Vecteur3D.cc general/inc/Vecteur3D.h general/inc/constantes.h
obj/constantes.o: general/src/constantes.cc general/inc/constantes.h
obj/Particule.o: general/src/Particule.cc general/inc/Particule.h general/inc/Vecteur3D.h general/inc/constantes.h general/inc/Element.h dessin/inc/Dessinable.h
obj/Element.o: general/src/Element.cc general/inc/Element.h general/inc/Particule.h dessin/inc/Dessinable.h
obj/Accelerateur.o: general/src/Accelerateur.cc general/inc/Accelerateur.h general/inc/Element.h dessin/inc/Dessinable.h dessin/inc/Support_a_dessin.h
obj/Vue_Texte.o: texte/src/Vue_Texte.cc texte/inc/Vue_Texte.h dessin/inc/Support_a_dessin.h general/inc/Accelerateur.h
obj/Dessinable.o: dessin/src/Dessinable.cc dessin/inc/Dessinable.h dessin/inc/Support_a_dessin.h

#testVecteur3D.o: testVecteur3D.cc Vecteur3D.h
#testParticule.o: testParticule.cc Particule.h
#testElement.o: testElement.cc Element.h
obj/testAccel1.o: tests/src/testAccel1.cc texte/inc/Vue_Texte.h dessin/inc/Support_a_dessin.h general/inc/Accelerateur.h
