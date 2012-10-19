
#ifndef __WPLUGIN_H_
  #define __WPLUGIN_H_

#include <QtPlugin>


class QString;



class WPlugin
{
public:
	virtual ~WPlugin() {}
	
	virtual void init() {}
	
	virtual QString name() const = 0;

};

Q_DECLARE_INTERFACE(WPlugin, "wolverine.plugins.WPlugin/0.1")


#endif //__WPLUGIN_H_