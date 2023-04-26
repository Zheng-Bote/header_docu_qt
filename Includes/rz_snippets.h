#pragma once

#include <QDir>
#include <QDebug>
#include <QPluginLoader>
#include <cstdlib>

#include "rz_header_docu_plugins.h"


class Snippets
{
public:
    Snippets();

    void checkBool(const bool &boolCheck);
    QStringList getPlugins(QString &path);
    bool testPlugins(QMap<QString, QString> &pluginMap, QStringList &plugins);
    void listPlugins(QStringList parserPlugins);

    void setCountedFiles();
    int getCountedFiles();

    void getDirsRecursive(QDir &root, QStringList filter);
    void getDirsRecursive(QDir &root,
                          QString &inputDir,
                          QString &outputDir,
                          QStringList filter,
                          QString pluginParser,
                          QString pluginWriter,
                          QString fileOutType,
                          QStringList map_ParseKeys);

private:
    int countedFiles{};
};
