! include( ../../common.pri ) {
	error( Couldn't find common.pri file! )
}


TEMPLATE    = lib

HEADERS    += qtmanagedtoolbar.h \
              qtmanagedtoolbardialog.h
			  
SOURCES    += qtmanagedtoolbar.cpp \
              qtmanagedtoolbardialog.cpp

RESOURCES  += resources.qrc

FORMS      += qtmanagedtoolbardialog.ui