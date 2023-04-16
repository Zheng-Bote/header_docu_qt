/**
 * @file rz_snippets.cpp
 * @author ZHENG Robert (www.robert.hase-zheng.net)
 * @brief lib for header_docu
 * @details ragpicker for unsorted methods
 * @version 0.6.0
 * @date 2023-04-15
 *
 * @copyright Copyright (c) ZHENG Robert 2023
 *
 */
#include "rz_snippets.h"


Snippets::Snippets()
{}

void Snippets::checkBool(const bool &boolCheck)
{
    if(boolCheck == false) {
        qCritical() << "program criterias missmatch";
        exit(1);
    }
}

QStringList Snippets::getPlugins(QString &path)
{
    QStringList plugins;
    QStringList filter;
    // Windows, Linux, Mac
    filter << "*.dll" << "*.so" << "*.dylib";

    QDir dir(path);
    QFileInfoList list = dir.entryInfoList(filter);
    foreach(QFileInfo file, list) {
        #ifdef Q_OS_LINUX
            plugins.append(file.filePath());
        #elif defined(Q_OS_MACX)
            if(!file.isSymLink()) {
                plugins.append(file.filePath());
            }
        #endif
    }

    return plugins;
}

bool Snippets::testPlugins(QMap<QString, QString> &pluginMap, QStringList &plugins)
{
    int countPlugins = plugins.length();

    foreach(QString file, plugins) {
        qDebug() << "Loading..." << file;

        QPluginLoader loader(file);
        if(!loader.load()) {
            qDebug() << "Error: " << loader.fileName() << " Error: " << loader.errorString();
            --countPlugins;
            continue;
        }

        qDebug() << "Loaded: " << loader.fileName();

        Plugin* plugin = qobject_cast<Plugin*>(loader.instance());
        if(plugin) {
            plugin->test("Test: header_docu plugin");
            pluginMap[plugin->getName()] = loader.fileName();
            qInfo() << "Plugin Name: " << plugin->getName();
            qInfo() << "Plugin Version: " << plugin->getVersion();
            //plugin->parseFile("/media/zb_bamboo/500GB/Dev/QT/header_docu_qt/ESP32_libs-main/rz_bme680.h");
            //plugin->writeFile("irgendwas Pfad Write");
            loader.unload();
        } else {
            qDebug() << "Could not cast: " << loader.fileName();
            --countPlugins;
        }
    }

    // no valid plugins
    if(countPlugins <= 0) {
        return false;
    }

    // at least 1 valid plugin
    return true;
}

void Snippets::getDirsRecursive(QDir &root, QStringList filter)
{
    qInfo() << "---Listing---";
        foreach(QFileInfo fi, root.entryInfoList(QDir::AllEntries | QDir::NoDotAndDotDot,QDir::Name))
        {
            if(fi.isDir())
            {
                QDir child(fi.filePath());
                qInfo() << "Inspecting Dir: " << child.absolutePath();
                Snippets::getDirsRecursive(child, filter);
            }
            else {
                qInfo() << "Folder: " << fi.path();
                QDir dir(fi.absolutePath());
                QFileInfoList list = dir.entryInfoList(filter);
                foreach(QFileInfo file, list) {
                    qInfo() << "File matched: " << file.fileName() << " " << file.absoluteFilePath();
                }
            }
        }
}


