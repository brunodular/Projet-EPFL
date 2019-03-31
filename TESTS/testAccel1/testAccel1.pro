CONFIG += c++11
CONFIG -= app_bundle

TARGET = testAccel1

LIBS += \
	-L../../general -lgeneral \

PRE_TARGETDEPS += \
	../../general/libgeneral.a \

INCLUDEPATH += \
	../../general \
	
SOURCES += \
	testAccel1.cc \
	vue_texte.cc

HEADERS += \
    ../../general/Accelerateur.h \
    vue_texte.h \
    ../../general/Dessinable.h \
    ../../general/Support_a_dessin.h

