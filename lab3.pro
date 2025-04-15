TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle

QT += sql

#HEADERS +=

SOURCES += main.cpp \
    src/extractdata.cpp

HEADERS += \
    src/extractdata.h

DISTFILES += \
    README.md \
    test\data\*
