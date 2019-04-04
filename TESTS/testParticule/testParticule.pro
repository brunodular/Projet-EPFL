CONFIG += c++11
CONFIG -= app_bundle

TARGET = testParticule

LIBS += \
	-L../../vue_texte -lvue_texte \
  -L../../general -lgeneral

PRE_TARGETDEPS += \
  ../../vue_texte/libvue_texte.a \
	../../general/libgeneral.a


INCLUDEPATH += \
	../../general \
	../../vue_texte

SOURCES = testParticule.cc

HEADERS += \
    ../../general/Particule.h \
    ../../vue_texte/vue_texte.h \
