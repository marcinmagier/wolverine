
INCLUDEPATH += $$PWD \
               $$PWD/qtactionmanager \
			   $$PWD/qtconfig
DEPENDPATH += $$PWD

QTMISCLIB_LIBNAME = qtmisclib
QTMISCLIB_LIBDIR = $$PWD/bin

uselib {
    LIBS += -L$$QTMISCLIB_LIBDIR -l$$QTMISCLIB_LIBNAME
} else {
    SOURCES   += $$PWD/qtactionmanager/qtaction.cpp \
                 $$PWD/qtactionmanager/qtactionmanager.cpp \
                 $$PWD/qtactionmanager/qtactionmanager_impl.cpp \
                 $$PWD/qtactionmanager/qtactionmanagerwidget.cpp \
                 $$PWD/qtconfig/qtconfig.cpp \
                 $$PWD/qtconfig/qtdialogsettings.cpp

    HEADERS   += $$PWD/qtactionmanager.h \
                 $$PWD/qtactionmanager/qtaction.h \
                 $$PWD/qtactionmanager/qtactionmanager_impl.h \
                 $$PWD/qtactionmanager/qtactionmanagerwidget.h \
                 $$PWD/qtconfig.h \
                 $$PWD/qtconfig/qtdialogsettings.h

    FORMS     += $$PWD/qtactionmanager/qtactionmanagerwidget.ui \
                 $$PWD/qtconfig/qtdialogsettings.ui
}
