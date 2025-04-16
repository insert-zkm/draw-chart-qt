TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle

QT += sql

#HEADERS +=
INCLUDEPATH += src/

SOURCES += main.cpp \
    src/extractdata.cpp

HEADERS += \
    src/extractdata.hpp \
    src/timeseries.hpp

DISTFILES += \
    README.md \
    test\data\*
