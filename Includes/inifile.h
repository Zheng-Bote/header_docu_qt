#ifndef INIFILE_H
#define INIFILE_H

#include <QString>
#include <iostream>
#include <QDir>
#include <QFile>
#include <QDebug>

/*
 * https://github.com/Rookfighter/inifile-cpp
 * #include "Includes/inicpp.h"
 */
#include "inicpp.h"

class Inifile
{
public:
    Inifile();
    Inifile(QString &progname);
    Inifile(QString &path, QString &file);
    ~Inifile();
    void Test();
    void createIni(QString &path);
    bool saveIniToFile(QString &path, QString &file);
    bool loadIni(QString &pathFile);

    QString getAttribs();
private:
    ini::IniFile myIni;
};

#endif // INIFILE_H
