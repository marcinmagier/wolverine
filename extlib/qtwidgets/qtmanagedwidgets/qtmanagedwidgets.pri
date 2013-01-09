
INCLUDEPATH += $$PWD

SOURCES      += \
                $$PWD/qtmanagedmenu.cpp \
                $$PWD/qtmanagedtoolbar.cpp \
                $$PWD/qtmanagedwidgetsdialog.cpp \
                $$PWD/qtmanagedwidgetslistbox.cpp

HEADERS      += \
                $$PWD/qtmanagedmenu.h \
                $$PWD/qtmanagedtoolbar.h \
                $$PWD/qtmanagedwidgetsdialog.h \
                $$PWD/qtmanagedwidgetslistbox.h

RESOURCES    += \
                $$PWD/qtmanagedwidgets.qrc

FORMS        += \
                $$PWD/qtmanagedwidgetsdialog.ui

TRANSLATIONS += \
                $$PWD/translations/qtmanagedwidgets_en_US.ts \
                $$PWD/translations/qtmanagedwidgets_pl_PL.ts
