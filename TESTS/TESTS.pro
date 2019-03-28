CONFIG += c++11

TARGET += \ 
	exerciceP10 \
	testAccel1 \
	testParticule \
	testVecteur3D

LIBS += \
	-L../general -lgeneral \
	-L../vue_texte -lvue_texte
	
PRE_TARGETDEPS += \
	../general/libgeneral.a \
	../vue_texte/libvue_texte.a
	
INCLUDEPATH += \
	../general \
	../vue_texte
	
SOURCES += \
	exerciceP10.cc \
	testAccel1.cc \
	testParticule.cc \
	testVecteur3D.cc

HEADERS += \
	../general/Accelerateur.h \
	../vue_texte/vue_texte.h \
	../general/Dessinable.h \
	../general/Support_a_dessin.h 
	
