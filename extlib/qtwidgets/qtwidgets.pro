TEMPLATE=lib
CONFIG += qt dll

#CONFIG += debug_and_release build_all

include(qtwidgets.pri)

TARGET = $$QTWIDGETS_LIBNAME
DESTDIR = $$QTWIDGETS_LIBDIR
