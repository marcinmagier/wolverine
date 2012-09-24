// main.cpp

#include "AppConfig.h"


int main(int argc, char *argv[])
{

    AppConfig *settings = AppConfig::getInstance();

    settings->loadConfiguration();
    settings->saveConfiguration();

    return 0;
}
