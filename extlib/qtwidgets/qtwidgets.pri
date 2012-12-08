
DEPENDPATH += $$PWD
INCLUDEPATH +=  $$PWD \
                $$PWD/qtmanagedtoolbar

QTWIDGETS_LIBNAME = qtwidgets
QTWIDGETS_LIBDIR = $$PWD/bin

uselib {
    LIBS += -L$$QTWIDGETS_LIBDIR -l$$QTWIDGETS_LIBNAME
} else {
    SOURCES      += \
                    $$PWD/qtpopup/qtpopup.cpp \
                    $$PWD/qtmanagedtoolbar/qtmanagedtoolbar.cpp \
                    $$PWD/qtmanagedtoolbar/qtmanagedtoolbardialog.cpp \
                    $$PWD/qtmanagedtoolbar/qtmanagedtoolbarlistbox.cpp

    HEADERS      += \
                    $$PWD/qtpopup.h \
                    $$PWD/qtmanagedtoolbar.h \
                    $$PWD/qtmanagedtoolbar/qtmanagedtoolbardialog.h \
                    $$PWD/qtmanagedtoolbar/qtmanagedtoolbarlistbox.h

    RESOURCES    += \
                    $$PWD/qtmanagedtoolbar/resources.qrc

    FORMS        += \
                    $$PWD/qtmanagedtoolbar/qtmanagedtoolbardialog.ui

    TRANSLATIONS += \
                    $$PWD/qtmanagedtoolbar/translations/qtmanagedtoolbar_en_US.ts \
                    $$PWD/qtmanagedtoolbar/translations/qtmanagedtoolbar_pl_PL.ts
}
