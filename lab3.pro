CONFIG += console c++11
CONFIG -= app_bundle

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

QT += sql charts core gui

INCLUDEPATH += src/ \
    src/mycharts/ \
    src/widgets/

SOURCES += main.cpp \
    src/extractdata.cpp \
    src/widgets/win.cpp \
    src/mycharts/mychart.cpp \
    src/parse.cpp

HEADERS += \
    src/chartdata.hpp \
    src/extractdata.hpp \
    src/widgets/win.hpp \
    src/mycharts/mychart.hpp \
    src/parse.hpp

DISTFILES += \
    README.md \
    test\data\*

QMAKE_DISTCLEAN += \
    README.md \
    test\*

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
