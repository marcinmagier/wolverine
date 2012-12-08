
DEPENDPATH += $$PWD
INCLUDEPATH +=  \
                $$PWD/qtmanagedtoolbar \
                $$PWD

QTWIDGETS_LIBNAME = qtwidgets
QTWIDGETS_LIBDIR = $$PWD/bin

uselib {
    LIBS += -L$$QTWIDGETS_LIBDIR -l$$QTWIDGETS_LIBNAME
} else {
    SOURCES      += \
                    $$PWD/qtmanagedtoolbar/qtmanagedtoolbar.cpp \
                    $$PWD/qtmanagedtoolbar/qtmanagedtoolbardialog.cpp \
                    $$PWD/qtmanagedtoolbar/qtmanagedtoolbarlistbox.cpp \
                    $$PWD/qtpopup/qtpopup.cpp \
                    $$PWD/qtpopup/qtpopupp.cpp

    HEADERS      += \
                    $$PWD/qtmanagedtoolbar.h \
                    $$PWD/qtmanagedtoolbar/qtmanagedtoolbardialog.h \
                    $$PWD/qtmanagedtoolbar/qtmanagedtoolbarlistbox.h \
                    $$PWD/qtpopup.h \
                    $$PWD/qtpopupp.h

    RESOURCES    += \
                    $$PWD/qtmanagedtoolbar/resources.qrc

    FORMS        += \
                    $$PWD/qtmanagedtoolbar/qtmanagedtoolbardialog.ui \
                    $$PWD/qtpopup/qtpopupp.ui

    TRANSLATIONS += \
                    $$PWD/qtmanagedtoolbar/translations/qtmanagedtoolbar_en_US.ts \
                    $$PWD/qtmanagedtoolbar/translations/qtmanagedtoolbar_pl_PL.ts
}

