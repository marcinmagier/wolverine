TEMPLATE=lib
CONFIG += qt warn_off dll thread

#CONFIG += debug_and_release build_all

include(qtscintilla.pri)

TARGET = $$QTSCINTILLA_LIBNAME
DESTDIR = $$QTSCINTILLA_LIBDIR
