CONFIG = staticlib -std=c++11 console
CONFIG -= app_bundle

QMAKE_CXX = g++ -std=c++11

EXT_LIBS = libgeneral.a

INCLUDEPATH = -I../../general

SOURCES += testVecteur3D.cc

HEADERS += ../../general/Vecteur3D.h ../../general/constantes.h

LIBS += -L../../general -libgeneral.a/

#PRE_TARGETDEPS = -libgeneral.a
