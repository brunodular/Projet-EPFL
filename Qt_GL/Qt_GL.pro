QT += core gui opengl widgets
CONFIG += c++11
CONFIG -= app_bundle

win32:LIBS += -lopengl32

TARGET = ex_gl

LIBS += -L../general -lgeneral
PRE_TARGETDEPS += ../general/libgeneral.a

INCLUDEPATH = ../general

SOURCES += \
    main_qt_gl.cc \
    glwidget.cc \
    glsphere.cc \
    vue_opengl.cc

HEADERS += \
    glwidget.h \
    vertex_shader.h \
    vue_opengl.h \
    glsphere.h \
    ../general/Dessinable.h \
    ../general/Support_a_dessin.h \
    ../general/Accelerateur.h \
    ../general/Case.h

RESOURCES += \
    resource.qrc
