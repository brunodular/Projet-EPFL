CONFIG += c++11
CONFIG -= app_bundle

TARGET = testParticule

LIBS += \
	-L../../general -lgeneral \

PRE_TARGETDEPS += \
	../../general/libgeneral.a \

INCLUDEPATH += \
	../../general \

SOURCES += \
	testParticule.cc \
	vue_texte.cc

HEADERS += \
    ../../general/Particule.h \
    vue_texte.h 
