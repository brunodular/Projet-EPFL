CONFIG += c++11

TARGET = ex_text

LIBS += \
	-L../general -lgeneral \
	-L../vue_texte -lvue_texte
	
PRE_TARGETDEPS += \
	../general/libgeneral.a \
	../vue_texte/libvue_texte.a

INCLUDEPATH += \
	../general \
	../vue_texte

SOURCES = main_text.cc

HEADERS += \
    ../general/Accelerateur.h \
    ../vue_texte/vue_texte.h \
    ../general/Dessinable.h \
    ../general/Support_a_dessin.h
