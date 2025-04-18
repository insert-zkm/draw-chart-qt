CONFIG += console c++11
CONFIG -= app_bundle

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

QT += sql charts core gui

INCLUDEPATH += src/ \
    src/mycharts/ \
    src/widgets/ \
    src/widgets/ComboBox

SOURCES += main.cpp \
    includes/filetablemodel.cpp \
    src/extractdata.cpp \
    src/widgets/chartwidget.cpp \
    src/widgets/filesystemwidget.cpp \
    src/widgets/win.cpp \
    src/mycharts/mychart.cpp \
    src/parse.cpp \
    includes/ComboBox/seperatorcombobox.cpp

HEADERS += \
    includes/filetablemodel.hpp \
    src/chartdata.hpp \
    src/extractdata.hpp \
    src/widgets/chartwidget.hpp \
    src/widgets/filesystemwidget.hpp \
    src/widgets/win.hpp \
    src/mycharts/mychart.hpp \
    src/parse.hpp \
    includes/ComboBox/seperatorcombobox.hpp

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
