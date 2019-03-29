QT += core gui opengl widgets
CONFIG += c++11
CONFIG -= app_bundle

win32:LIBS += -lopengl32

TARGET = exerciceP12

INCLUDEPATH += \
    ../../general \
    ../../Qt_GL

LIBS += -L../../general -lgeneral
PRE_TARGETDEPS += ../../general/libgeneral.a

SOURCES += \
    exerciceP12.cc

HEADERS += \
    ../../Qt_GL/glwidget.h

RESOURCES += \
    ../../Qt_GL/resource.qrc
