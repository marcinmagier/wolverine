/**************************************************************************************************
**
** Copyright (C) 2012-2013 Magier Marcin.
**
**
**************************************************************************************************/

/**
 *  @file       WLib.cpp
 *  @brief      Wolverine library implementation.
 */


#include "WLib.h"

#include <QString>
#include <QStringList>
#include <QFileInfo>


#define W_FILE_LINE_SEP "@"

using namespace Wolverine;


Lib::Lib()
{

}


/**
 *  Creates string formatted with <filepath>|<line> pattern from parametes.
 *
 * @param path
 * @param line
 * @return
 */
//static
QString Lib::createFileName(const QString &path, const int line)
{
    QString file;
    return file.append(W_FILE_LINE_SEP).append(QString::number(line));
}


/**
 *  Creates string formatted with <filepath>|<line> pattern from parametes.
 *
 * @param path
 * @param line
 * @return
 */
//static
QString Lib::createFileName(const QString &path, const QString &line)
{
    int lineint = line.toInt();
    QString file;

    return file.append(W_FILE_LINE_SEP).append(QString::number(lineint));
}


/**
 *  Creates list of files formatted with <filepath>|<line> pattern from
 *  command line arguments.
 *
 * @param argc
 * @param argv
 * @return
 */
//static
QStringList Lib::createFileListFromArgs(int argc, char **argv)
{
    QStringList files;

    // Check last argument as it can be a line number.
    bool isLineNum = false;
    int lineGlob = QString(argv[argc-1]).toInt(&isLineNum);
    int noOfArgs = isLineNum ? argc-1 : argc;

    // Omit first argument (application path)
    for(int i=1; i<noOfArgs; ++i) {
        QStringList tmp = QString(argv[i]).split(W_FILE_LINE_SEP);
        QFileInfo file(tmp[0]);
        bool isLocalLine = false;
        int lineLocal = QString(tmp[1]).toInt(&isLocalLine);

        if(file.exists()) {
            int line = isLocalLine ? lineLocal : lineGlob;
            files.append(createFileName(file.absoluteFilePath(), line));
        }
    }
    return files;
}


/**
 *  Retrieves file path from string formated with <filepath>|<line> pattern
 *
 * @param file
 * @return
 */
//static
QString Lib::getPathFromFile(const QString &file)
{
    QStringList tmp = file.split(W_FILE_LINE_SEP);
    return tmp.value(0);
}


/**
 *  Retrieves line from string formated with <filepath>|<line> pattern
 *
 * @param file
 * @return
 */
//static
int Lib::getLineFromFile(const QString &file)
{
    QStringList tmp = file.split(W_FILE_LINE_SEP);
    return tmp.value(1).toInt();
}
