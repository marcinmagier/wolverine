
INCLUDEPATH += $$PWD
DEPENDPATH += $$PWD

QTWIDGETS_LIBNAME = qtwidgets
QTWIDGETS_LIBDIR = $$PWD/bin

uselib {
    LIBS += -L$$QTWIDGETS_LIBDIR -l$$QTWIDGETS_LIBNAME
} else {
    SOURCES      += \
                    $$PWD/src/qtpopup.cpp

    HEADERS      += \
                    $$PWD/qtpopup.h

#    RESOURCES    += \

#    FORMS        += \

#    TRANSLATIONS += \
}
