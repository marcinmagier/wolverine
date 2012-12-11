
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
                    $$PWD/qtpopup/qtpopup_i.cpp \
                    $$PWD/qtpopup/qtpopup_flash.cpp \
                    $$PWD/qtpopup/qtpopup_move.cpp

    HEADERS      += \
                    $$PWD/qtmanagedtoolbar.h \
                    $$PWD/qtmanagedtoolbar/qtmanagedtoolbardialog.h \
                    $$PWD/qtmanagedtoolbar/qtmanagedtoolbarlistbox.h \
                    $$PWD/qtpopup.h

    RESOURCES    += \
                    $$PWD/qtmanagedtoolbar/resources.qrc

    FORMS        += \
                    $$PWD/qtmanagedtoolbar/qtmanagedtoolbardialog.ui \
                    $$PWD/qtpopup/qtpopup.ui

    TRANSLATIONS += \
                    $$PWD/qtmanagedtoolbar/translations/qtmanagedtoolbar_en_US.ts \
                    $$PWD/qtmanagedtoolbar/translations/qtmanagedtoolbar_pl_PL.ts
}

