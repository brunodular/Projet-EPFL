CONFIG += c++11

TARGET = ex_text

LIBS += \
	-L../general -lgeneral \
	
PRE_TARGETDEPS += \
	../general/libgeneral.a \

INCLUDEPATH += \
	../general \

SOURCES += \
	main_text.cc \
	vue_texte.cc

HEADERS += \
    ../general/Accelerateur.h \
    vue_texte.h \
    ../general/Dessinable.h \
    ../general/Support_a_dessin.h
