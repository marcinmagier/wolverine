
INCLUDEPATH += $$PWD
DEPENDPATH += $$PWD

QTMANAGEDTOOLBAR_LIBNAME = qtmanagedtoolbar
QTMANAGEDTOOLBAR_LIBDIR = $$PWD/bin

uselib {
    LIBS += -L$$QTMANAGEDTOOLBAR_LIBDIR -l$$QTMANAGEDTOOLBAR_LIBNAME
} else {
    SOURCES      += \
                    $$PWD/qtmanagedtoolbar.cpp \
                    $$PWD/qtmanagedtoolbardialog.cpp \
                    $$PWD/qtmanagedtoolbarlistbox.cpp

    HEADERS      += \
                    $$PWD/qtmanagedtoolbar.h \
                    $$PWD/qtmanagedtoolbardialog.h \
                    $$PWD/qtmanagedtoolbarlistbox.h

    RESOURCES    += \
                    $$PWD/resources.qrc

    FORMS        += \
                    $$PWD/qtmanagedtoolbardialog.ui

    TRANSLATIONS += \
                    $$PWD/translations/qtmanagedtoolbar_en_US.ts \
                    $$PWD/translations/qtmanagedtoolbar_pl_PL.ts
}
