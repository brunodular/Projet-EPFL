CONFIG += c++11
CONFIG -= app_bundle

TARGET = testVecteur3D

LIBS += \
	-L../../general -lgeneral

PRE_TARGETDEPS += \
	../../general/libgeneral.a

INCLUDEPATH += \
	../../general

SOURCES = testVecteur3D.cc

HEADERS += \
    ../../general/Vecteur3D.h
