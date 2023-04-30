/**
 * @file rz_snippets.cpp
 * @author ZHENG Robert (www.robert.hase-zheng.net)
 * @brief lib for header_docu
 * @details ragpicker for unsorted methods
 * @version 0.7.0
 * @date 2023-04-15
 *
 * @copyright Copyright (c) ZHENG Robert 2023
 *
 */
#include "rz_snippets.h"

#include "rz_dirfileinfo.h"
#include "rz_inoutput.h"

#ifndef TARGET_OS_MAC
#include <QThread>
#include <QThreadPool>
#endif
#include "rz_dofile.h"
#include <iostream>

Snippets::Snippets()
{
    countedFiles = 0;
}

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
        #ifndef Q_OS_MACX
            plugins.append(file.filePath());
        #else
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

void Snippets::listPlugins(QStringList plugins)
{
    foreach (QString file, plugins) {
        QPluginLoader loader(file);
        if (!loader.load()) {
            qDebug() << "Error: " << loader.fileName() << " Error: " << loader.errorString();
            continue;
        } else {
            Plugin *plugin = qobject_cast<Plugin *>(loader.instance());
            if (plugin) {
                std::cout << std::left << std::setfill('.') << std::setw(20)
                          << "Plugin Name:" << plugin->getName().toStdString() << std::endl;
                std::cout << std::left << std::setfill('.') << std::setw(20)
                          << "Version:" << plugin->getVersion().toStdString() << std::endl;
                //qInfo() << "Plugin Name: " << plugin->getName() << "(" << plugin->getVersion() << ")";
                loader.unload();
            } else {
                qDebug() << "Could not cast: " << loader.fileName();
            }
        }
    }
}

void Snippets::setCountedFiles(int count)
{
    countedFiles = countedFiles + count;
}

int Snippets::getCountedFiles()
{
    return countedFiles;
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

void Snippets::getDirsRecursive(QDir &root,
                                QString &inputdir,
                                QString &outputdir,
                                QStringList filter,
                                QString pluginParser,
                                QString pluginWriter,
                                QString fileOutType,
                                QStringList map_ParseKeys)
{
#ifndef TARGET_OS_MAC

        QThread::currentThread()->setObjectName("getDirsRecursive");
        //qInfo() << "Main: " << QThread::currentThread();
        QThreadPool pool;
#endif

        QDir inputDir(inputdir);
        //qInfo() << "---Listing---";
        foreach(QFileInfo fi, inputDir.entryInfoList(QDir::AllEntries | QDir::NoDotAndDotDot,QDir::Name))
        {
            if(fi.isDir())
            {
                QDir child(fi.filePath());
                // qInfo() << "Inspecting Dir: " << child.absolutePath();
                Snippets::getDirsRecursive(child, filter);
            }
            else {
                // qInfo() << "Folder: " << fi.path();
                QDir dir(fi.absolutePath());
                QFileInfoList list = dir.entryInfoList(filter);
                setCountedFiles(list.length());

                foreach(QFileInfo file, list) {
                    //qInfo() << "File matched: " << file.fileName() << " " << file.absoluteFilePath();
                    QString pathToFile = file.absoluteFilePath();
                    DirFileInfo df(pathToFile);
                    df.addMapParseKeys(map_ParseKeys);
                    InputOutput* ioSingle = new InputOutput();
                    ioSingle->setpParser(pluginParser);
                    ioSingle->setwParser(pluginWriter);
                    ioSingle->setData(df.mapParseKeys,df.mapFileAttribs);
                    //QString outPutFile = Inifile.getOutputDir() + "/" + df.mapFileAttribs["FILE_Name"] + "." + fileOutType;
                    QString outPutFile = ioSingle->setOutputDir(inputdir, outputdir, file.absolutePath());
                    //qInfo() << "\n\ntarget: " << outPutFile;
                    ioSingle->makeOutputDir(outPutFile);
                    outPutFile.append("/" + df.mapFileAttribs["FILE_baseFileName"] + "." + fileOutType); // ".json"); // + pluginWriter);
                    //qInfo() << "target file: " << outPutFile;
                    ioSingle->setFiles(pathToFile, outPutFile);
                    //ioSingle->runner();

                    DoFile *dofile = new DoFile();
                    dofile->inFile = pathToFile;
                    dofile->outFile = outPutFile;
                    dofile->mapFileAttribs = df.mapFileAttribs;
                    dofile->mapParseKeys = df.mapParseKeys;
                    dofile->pPluginPath = pluginParser;
                    dofile->wPluginPath = pluginWriter;
                    dofile->setAutoDelete(true);
                    #ifndef TARGET_OS_MAC
                    pool.start(dofile);
                    //pool.waitForDone();
                    #else
                    dofile->run();
                    #endif

                }
            }
        }
        #ifndef TARGET_OS_MAC
        pool.waitForDone();
        #endif
}


