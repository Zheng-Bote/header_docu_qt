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

    // Input
    QString getInputDir();
    QStringList getInputExtensions();
    // Meta
    QStringList getAttributes();
    QStringList getMetadata();
    // Output
    QString getOutputDir();
    QString getFileType();
    bool isSingleFileOutput();
    // Plugins
    QString getParserPluginsDir();
    QString getWriterPluginsDir();

    // Input
    QString setInputDir(std::string inputDir);
    QStringList setInputExtensions(std::string inputExtension);
    // Meta
    // QStringList setAttributes();
    // QStringList setMetadata();
    // Output
    QString setOutputDir(std::string outputDir);
    QString setFileType(std::string fileType);
    // bool setSingleFileOutput();
    // Plugins
    // QString setParserPluginsDir(QString parserPluginDir);
    // QString setWriterPluginsDir(QString writerPluginDir);


    void listIniEntries();

    bool checkIniInputs();
    bool checkIniMeta();
    bool checkIniOutputs();
    bool checkIniPlugins(Snippets &Snippets, QMap<QString, QString> &pluginParserMap, QMap<QString, QString> &pluginWriterMap);

private:
    ini::IniFile myIni;
};


