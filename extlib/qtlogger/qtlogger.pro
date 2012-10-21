QT       -= gui
TEMPLATE  = lib
CONFIG   += qt dll

#CONFIG   += debug_and_release build_all

include(qtlogger.pri)

TARGET = $$QTLOGGER_LIBNAME
DESTDIR = $$QTLOGGER_LIBDIR

