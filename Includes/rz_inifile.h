#pragma once

#include <QString>
#include <iostream>
#include <QDir>
#include <QFile>
#include <QDebug>

/* https://github.com/Rookfighter/inifile-cpp */
#include "inicpp.h"

#include "rz_snippets.h"

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
    void listIniEntries();

    bool checkIniInputs();
    bool checkIniMeta();
    bool checkIniOutputs();
    bool checkIniPlugins(Snippets &Snippets, QMap<QString, QString> &pluginMap);

private:
    ini::IniFile myIni;
};


