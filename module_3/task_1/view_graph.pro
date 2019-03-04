TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    clistgraph.cpp \
    cmatrixgraph.cpp \
    carcgraph.cpp \
    csetgraph.cpp

HEADERS += \
    igraph.h \
    clistgraph.h \
    cmatrixgraph.h \
    carcgraph.h \
    csetgraph.h
