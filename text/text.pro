CONFIG += c++11

TARGET = ex_text

LIBS += -L../general -lgeneral
PRE_TARGETDEPS += ../general/libgeneral.a

INCLUDEPATH = ../general

SOURCES += \
    main_text.cc \
    Vue_Texte.cc

HEADERS += \
    ../general/Accelerateur.h \
    Vue_Texte.h \
    ../general/Dessinable.h \
    ../general/Support_a_dessin.h
