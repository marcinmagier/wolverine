
INCLUDEPATH += $$PWD
DEPENDPATH += $$PWD
QT *= network

QTSINGLEAPPLICATION_LIBNAME = qtsingleapplication
QTSINGLEAPPLICATION_LIBDIR = $$PWD/bin

uselib {
    LIBS += -L$$QTSINGLEAPPLICATION_LIBDIR -l$$QTSINGLEAPPLICATION_LIBNAME
} else {
    SOURCES += $$PWD/qtsingleapplication.cpp \
               $$PWD/qtlocalpeer.cpp

    HEADERS += $$PWD/qtsingleapplication.h \
               $$PWD/qtlocalpeer.h
}
