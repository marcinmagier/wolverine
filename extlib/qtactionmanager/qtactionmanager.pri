
INCLUDEPATH += $$PWD
DEPENDPATH += $$PWD

QTACTIONMANAGER_LIBNAME = qtactionmanager
QTACTIONMANAGER_LIBDIR = $$PWD/bin

uselib {
    LIBS += -L$$QTACTIONMANAGER_LIBDIR -l$$QTACTIONMANAGER_LIBNAME
} else {
    SOURCES   += $$PWD/qtaction.cpp \
                 $$PWD/qtactionmanager.cpp \
                 $$PWD/qtactionmanagerwidget.cpp

    HEADERS   += $$PWD/qtaction.h \
                 $$PWD/qtactionmanager.h \
                 $$PWD/qtactionmanagerwidget.h

    FORMS     += $$PWD/qtactionmanagerwidget.ui
}

HEADERS += \
    ../extlib/qtactionmanager/qtactionmanager_prv.h

SOURCES += \
    ../extlib/qtactionmanager/qtactionmanager_prv.cpp
