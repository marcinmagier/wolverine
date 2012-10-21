
INCLUDEPATH += $$PWD
DEPENDPATH += $$PWD

QTLOGGER_LIBNAME = qtlogger
QTLOGGER_LIBDIR = $$PWD/bin


uselib {
    LIBS += -L$$QTLOGGER_LIBDIR -l$$QTLOGGER_LIBNAME
} else {
    DEFINES   += CUTELOGGER_LIBRARY

    SOURCES   += $$PWD/Logger.cpp \
                 $$PWD/AbstractAppender.cpp \
                 $$PWD/AbstractStringAppender.cpp \
                 $$PWD/ConsoleAppender.cpp \
                 $$PWD/FileAppender.cpp

    HEADERS   += $$PWD/Logger.h \
                 $$PWD/CuteLogger_global.h \
                 $$PWD/AbstractAppender.h \
                 $$PWD/AbstractStringAppender.h \
                 $$PWD/ConsoleAppender.h \
                 $$PWD/FileAppender.h

    win32 {
        SOURCES += $$PWD/OutputDebugAppender.cpp
        HEADERS += $$PWD/OutputDebugAppender.h
    }
}
