CONFIG += c++11
CONFIG -= app_bundle

TARGET = exerciceP13

LIBS += \
	-L../../general -lgeneral \
	-L../../vue_texte -lvue_texte

PRE_TARGETDEPS += \
	../../general/libgeneral.a \
	../../vue_texte/libvue_texte.a

INCLUDEPATH += \
	../../general \
	../../vue_texte

SOURCES = test_evolution_polygone_regulier.cc

HEADERS += \
    ../../general/Accelerateur.h \
    ../../vue_texte/vue_texte.h \
