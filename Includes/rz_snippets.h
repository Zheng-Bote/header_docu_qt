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

    void getDirsRecursive(QDir &root, QStringList filter);
};
