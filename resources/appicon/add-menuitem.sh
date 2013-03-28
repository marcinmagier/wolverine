#!/bin/bash
 
APP_NAME=wolverine

xdg-desktop-menu install $APP_NAME.desktop

xdg-icon-resource install --size  16 $APP_NAME-16.png  $APP_NAME
xdg-icon-resource install --size  32 $APP_NAME-32.png  $APP_NAME
xdg-icon-resource install --size  48 $APP_NAME-48.png  $APP_NAME
