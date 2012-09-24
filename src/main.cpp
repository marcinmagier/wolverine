// main.cpp

#include "AppSettings.h"


int main(int argc, char *argv[])
{

    AppSettings settings;

    settings.readSettings();
    settings.writeSettings();

    return 0;
}
