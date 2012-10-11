TEMPLATE=lib
CONFIG += qt dll

#CONFIG += release build_all

include(qtsingleapplication.pri)

TARGET = $$QTSINGLEAPPLICATION_LIBNAME
DESTDIR = $$QTSINGLEAPPLICATION_LIBDIR

#win32 {
#    DLLDESTDIR = $$[QT_INSTALL_BINS]
#    QMAKE_DISTCLEAN += $$[QT_INSTALL_BINS]\\$${QTSINGLEAPPLICATION_LIBNAME}.dll
#}

#win32 {
#    contains(TEMPLATE, lib):contains(CONFIG, shared):DEFINES += QT_QTSINGLEAPPLICATION_EXPORT
#    else:qtsingleapplication-uselib:DEFINES += QT_QTSINGLEAPPLICATION_IMPORT
#}

#target.path = $$DESTDIR
#INSTALLS += target

