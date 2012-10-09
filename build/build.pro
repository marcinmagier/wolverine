! include( ../common.pri ) {
	error( Couldn't find common.pri file! )
}


TARGET = Wolverine
TEMPLATE = app

SOURCES += \
    ../src/main.cpp \
    ../src/settings/AppConfig.cpp \
    ../extlib/qtconfig/qtconfig.cpp

HEADERS  += \
    ../src/settings/ScintillaSettings.h \
    ../src/settings/HiddenSettings.h \
    ../src/settings/GeneralSettings.h \
    ../src/settings/AppConfig.h \
    ../extlib/qtconfig/qtconfig.h 

INCLUDEPATH += ../extlib/qtconfig \
    ../extlib/qtmanagedtoolbar \
    ../src/settings

RESOURCES += \
    ../resources/images.qrc 

LIBS += -L ../extlib/qtmanagedtoolbar/debug -lqtmanagedtoolbar