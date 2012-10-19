
#include "TestPlugin.h"
#include <QString>



QString TestPlugin::name() const
{
	return "TestPlugin";
}


Q_EXPORT_PLUGIN2(testplugin, TestPlugin)
