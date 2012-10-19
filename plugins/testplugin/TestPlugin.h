
#ifndef __TEST_PLUGIN_H_
  #define __TEST_PLUGIN_H_
  
#include "WPlugin.h"
#include <QObject>


class TestPlugin : public QObject, public WPlugin
{
    Q_OBJECT
	Q_INTERFACES(WPlugin)

public:
	virtual QString name() const ;
};

#endif //__TEST_PLUGIN_H_
