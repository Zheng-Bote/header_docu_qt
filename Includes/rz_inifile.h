#ifndef RZ_INIFILE_H
#define RZ_INIFILE_H

#include <QString>
#include <QFile>
#include <QDebug>

/* https://github.com/Rookfighter/inifile-cpp */
#include "inicpp.h"

class RZ_Inifile
{
public:
    RZ_Inifile();
    ini::IniFile &createInstance();
    bool createIni(ini::IniFile &myIni, QString path, QString file);
    bool loadIni(ini::IniFile &myIni, QString &path, QString &file);
};

#endif // RZ_INIFILE_H
