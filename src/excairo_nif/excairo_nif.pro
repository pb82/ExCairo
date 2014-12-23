TEMPLATE = lib
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

INCLUDEPATH += /usr/lib/erlang/erts-6.3/include/
INCLUDEPATH += /usr/include/cairo

QMAKE_CFLAGS += -Wno-missing-field-initializers -Wno-unused-parameter

SOURCES += excairo_nif.c
LIBS += -lcairo

include(deployment.pri)
qtcAddDeployment()

HEADERS += \
    include/excairo_nif.h

