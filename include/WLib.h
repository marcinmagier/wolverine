/**************************************************************************************************
**
** Copyright (C) 2012-2013 Magier Marcin.
**
**
**************************************************************************************************/

/**
 *  @file       WLib.h
 *  @brief      Wolverine library.
 *  @details    Contains general functions.
 */


#ifndef __W_LIB_H_
 #define __W_LIB_H_

class QString;
class QStringList;


namespace Wolverine
{


class Lib
{

public:
    Lib();

    static QString createFileName(const QString &path, const int line);
    static QString createFileName(const QString &path, const QString &line);
    static QStringList createFileListFromArgs(int argc, char **argv);
    static QString getPathFromFile(const QString &file);
    static int getLineFromFile(const QString &file);
};


}

#endif // __W_LIB_H_
