TEMPLATE = lib

CONFIG = staticlib c++11

SOURCES += \
	Accelerateur.cc \
	Faisceau.cc \
	Particule.cc \
	Element.cc \
	Vecteur3D.cc \
	constantes.cc

HEADERS += \
    Accelerateur.h \
    Dessinable.h \
    Support_a_dessin.h \
    Vecteur3D.h \
    Particule.h \
    Element.h \
    constantes.h
