CONFIG += c++11
CONFIG -= app_bundle

TARGET = exerciceP11

LIBS += \
	-L../../general -lgeneral \
	-L../../vue_texte -ltexte

PRE_TARGETDEPS += \
	../../general/libgeneral.a \
	../../vue_texte/lvue_texte.a 

INCLUDEPATH += \
	../../general \
	
SOURCES += \
	exerciceP11.cc

HEADERS += \
    ../../general/Accelerateur.h \
    ../../vue_texte/vue_texte.h \
    ../../general/Dessinable.h \
    ../../general/Support_a_dessin.h


