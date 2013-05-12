#-------------------------------------------------
#
# Project created by QtCreator 2013-03-30T09:56:43
#
#-------------------------------------------------


TEMPLATE = app
LIBS += -lGLU
QT += opengl
HEADERS = OGLQuad.h \
    OGLPyramid.h \
    OGLPyramid.h \
    light.h \
    scene3d.h
SOURCES += main.cpp \
    OGLQuad.cpp \
    OGLPyramid.cpp \
    light.cpp \
    scene3d.cpp
TARGET = ../OGLQuad
