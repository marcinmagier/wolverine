#!/bin/bash

APP_NAME=wolverine


xdg-desktop-menu uninstall $APP_NAME.desktop

xdg-icon-resource uninstall --size  16 $APP_NAME
xdg-icon-resource uninstall --size  32 $APP_NAME
xdg-icon-resource uninstall --size  48 $APP_NAME
