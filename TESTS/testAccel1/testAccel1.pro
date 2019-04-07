CONFIG += c++11
CONFIG -= app_bundle

TARGET = testAccel1

LIBS += \
	-L../../general -lgeneral \
	-L../../vue_texte -lvue_texte

PRE_TARGETDEPS += \
	../../general/libgeneral.a \
	../../vue_texte/libvue_texte.a
	
INCLUDEPATH += \
	../../general \
	../../vue_texte
	
SOURCES = testAccel1.cc 

HEADERS += \
    ../../general/Accelerateur.h \
    ../../vue_texte/vue_texte.h 


