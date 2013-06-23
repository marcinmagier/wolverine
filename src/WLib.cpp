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

#include <QApplication>
#include <QProcess>
#include <QFileInfo>
#include <QStringList>


#define W_FILE_LINE_SEP "?"

using namespace Wolverine;

QString Lib::sAppFile;



/**
 *  Creates string formatted with <filepath>@<line> pattern from parametes.
 *
 * @param path
 * @param line
 * @return
 */
//static
QString Lib::createFileName(const QString &path, const int line)
{
    QString file(path);
    return file.append(W_FILE_LINE_SEP).append(QString::number(line));
}


/**
 *  Creates string formatted with <filepath>@<line> pattern from parametes.
 *
 * @param path
 * @param line
 * @return
 */
//static
QString Lib::createFileName(const QString &path, const QString &line)
{
    int lineint = line.toInt();
    QString file(path);

    return file.append(W_FILE_LINE_SEP).append(QString::number(lineint));
}


/**
 *  Creates list of files formatted with <filepath>@<line> pattern from
 *  command line arguments.
 *
 * @param argc
 * @param argv
 * @return
 */
//static
QStringList Lib::createFileListFromArgs(int argc, char **argv)
{
    // We expect the following format:
    // <path1>[@<local_line1>] <path2>[@<local_line2>] ... [<global_line>]

    QStringList files;

    // Check last argument as it can be a global line number.
    bool isGlobalLine = false;
    int lineGlob = QString(argv[argc-1]).toInt(&isGlobalLine);
    int noOfArgs = isGlobalLine ? argc-1 : argc;

    // Omit first argument (application path)
    for(int i=1; i<noOfArgs; ++i) {
        QString str(argv[i]);
        if(str.compare("-n")==0 || str.compare("--new")==0)
            continue;

        QStringList tmp = str.split(W_FILE_LINE_SEP);
        QFileInfo file(tmp[0]);
        bool isLocalLine = false;
        int lineLocal = 0;
        if(tmp.length() > 1)
            lineLocal = QString(tmp[1]).toInt(&isLocalLine);

        // Local line has higher priorytet than global
        int line = isLocalLine ? lineLocal : lineGlob;
        files.append(createFileName(file.absoluteFilePath(), line));
    }
    return files;
}


/**
 *  Retrieves file path from string formated with <filepath>@<line> pattern
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
 *  Retrieves line from string formated with <filepath>@<line> pattern
 *
 * @param file
 * @return
 */
//static
int Lib::getLineFromFile(const QString &file)
{
    QStringList tmp = file.split(W_FILE_LINE_SEP);
    if(tmp.length() > 1)
        return tmp.value(1).toInt();
    return -1;
}


void Lib::setAppFile(const QString &appFile)
{
    sAppFile = appFile;
}


void Lib::openNewInstance(const QString &path)
{
    QStringList arguments;
    arguments << "--new";
    arguments << path;

    QProcess *newProc = new QProcess(qApp);
    newProc->start(sAppFile, arguments);
}
