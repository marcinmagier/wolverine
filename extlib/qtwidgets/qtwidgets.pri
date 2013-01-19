
DEPENDPATH += $$PWD
INCLUDEPATH +=  \
                $$PWD/qtmanagedwidgets \
                $$PWD

QTWIDGETS_LIBNAME = qtwidgets
QTWIDGETS_LIBDIR = $$PWD/bin

uselib {
    LIBS += -L$$QTWIDGETS_LIBDIR -l$$QTWIDGETS_LIBNAME
} else {
    SOURCES      += \
                    $$PWD/qtcolorbutton/qtcolorbutton.cpp \
                    $$PWD/qtlabel/qtlabel.cpp \
                    $$PWD/qtmanagedwidgets/qtmanagedmenu.cpp \
                    $$PWD/qtmanagedwidgets/qtmanagedtoolbar.cpp \
                    $$PWD/qtmanagedwidgets/qtmanagedwidgetsdialog.cpp \
                    $$PWD/qtmanagedwidgets/qtmanagedwidgetslistbox.cpp \
                    $$PWD/qtpopup/qtpopup.cpp \
                    $$PWD/qtpopup/qtpopup_base.cpp \
                    $$PWD/qtpopup/qtpopup_flash.cpp \
                    $$PWD/qtpopup/qtpopup_move.cpp \
                    $$PWD/qtpopup/qtpopup_rise.cpp \
                    $$PWD/qttabbar/qttabbar.cpp \
                    $$PWD/qttabwidget/qttabwidget.cpp

    HEADERS      += \
                    $$PWD/qtcolorbutton.h \
                    $$PWD/qtlabel.h \
                    $$PWD/qtmanagedmenu.h \
                    $$PWD/qtmanagedtoolbar.h \
                    $$PWD/qtmanagedwidgets/qtmanagedwidgetsdialog.h \
                    $$PWD/qtmanagedwidgets/qtmanagedwidgetslistbox.h \
                    $$PWD/qtpopup.h \
                    $$PWD/qttabbar.h \
                    $$PWD/qttabwidget.h

    RESOURCES    += \
                    $$PWD/qtmanagedwidgets/qtmanagedwidgets.qrc \
                    $$PWD/qttabbar/qttabbar.qrc


    FORMS        += \
                    $$PWD/qtmanagedwidgets/qtmanagedwidgetsdialog.ui \
                    $$PWD/qtpopup/qtpopup.ui

    TRANSLATIONS += \
                    $$PWD/qtmanagedwidgets/translations/qtmanagedwidgets_en_US.ts \
                    $$PWD/qtmanagedwidgets/translations/qtmanagedwidgets_pl_PL.ts
}

