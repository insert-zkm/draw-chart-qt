TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle

QT += sql charts

#HEADERS +=
INCLUDEPATH += src/ \
    src/mycharts/

SOURCES += main.cpp \
    src/extractdata.cpp \
    src/mycharts/mychart.cpp \
    src/parse.cpp

HEADERS += \
    src/chartdata.hpp \
    src/extractdata.hpp \
    src/mycharts/mychart.hpp \
    src/parse.hpp

DISTFILES += \
    README.md \
    test\data\*
