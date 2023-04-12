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
            plugin->parseFile("irgendwas Pfad Parse");
            plugin->writeFile("irgendwas Pfad Write");
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


