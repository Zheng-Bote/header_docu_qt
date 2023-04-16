/**
 * @file rz_inoutput.cpp
 * @author ZHENG Robert (www.robert.hase-zheng.net)
 * @brief lib for header_docu
 * @details class with threaded methods for Input / Output
 * @version 0.6.0
 * @date 2023-04-15
 *
 * @copyright Copyright (c) ZHENG Robert 2023
 *
 */

#include "rz_inoutput.h"


void test() {
    qInfo() << "InputOutput (test): " << QThread::currentThread();

    // parser
    QPluginLoader loader("/media/zb_bamboo/500GB/Dev/QT/header_docu_qt/build-header_docu_qt-Desktop_Qt_6_5_0_GCC_64bit-Debug/Plugins/parser/libhd_ghmd_parser_plugin.so");
    if(!loader.load()) {
        qDebug() << "Error: " << loader.fileName() << " Error: " << loader.errorString();
        //return;
    }

    qDebug() << "Loaded: " << loader.fileName();

    Plugin* plugin = qobject_cast<Plugin*>(loader.instance());
    if(plugin) {
        qInfo() << "Plugin loaded: " << plugin->getVersion();
        plugin->parseFile("/media/zb_bamboo/500GB/Dev/QT/header_docu_qt/ESP32_libs-main/rz_bme680.h");
    }

    // writer
    QPluginLoader wLoader("/media/zb_bamboo/500GB/Dev/QT/build-header_docu_qt-Desktop_Qt_6_5_0_GCC_64bit-Debug/Plugins/writer/libhd_json_writer_plugin.so");
    if(!wLoader.load()) {
        qDebug() << "Error: " << wLoader.fileName() << " Error: " << wLoader.errorString();
        //return;
    }

    qDebug() << "Loaded: " << wLoader.fileName();

    Plugin* wPlugin = qobject_cast<Plugin*>(wLoader.instance());
    if(wPlugin) {
        qInfo() << "Plugin loaded: " << wPlugin->getVersion();
        //wPlugin->writeFile(mapParseKeys, mapFileAttribs, "/media/zb_bamboo/500GB/Dev/QT/build-header_docu_qt-Desktop_Qt_6_5_0_GCC_64bit-Debug/Outputs/test.json");
    }
}

InputOutput::InputOutput(QObject *parent) : QObject(parent)
{
    QThread::currentThread()->setObjectName("InputOutput");
    qInfo() << "InputOutput: " << QThread::currentThread();
}

InputOutput::~InputOutput()
{

}

void InputOutput::run()
{
    qInfo() << "InputOutput (run): " << QThread::currentThread();
    //QFuture<void> future = QtConcurrent::run(&pool, test);
    test();
}

void InputOutput::runner()
{
    QPluginLoader pLoader(pPluginPath);
    if(!pLoader.load()) {
        qDebug() << "Error: " << pLoader.fileName() << " Error: " << pLoader.errorString();
        //return;
    }

    qDebug() << "Loaded: " << pLoader.fileName();

    Plugin* pPlugin = qobject_cast<Plugin*>(pLoader.instance());
    if(pPlugin) {
        qInfo() << "Plugin loaded: " << pPlugin->getVersion();
        pPlugin->writeFile(mapParseKeys, mapFileAttribs, outFile);
    }

    QPluginLoader wLoader(wPluginPath);
    if(!wLoader.load()) {
        qDebug() << "Error: " << wLoader.fileName() << " Error: " << wLoader.errorString();
        //return;
    }

    qDebug() << "Loaded: " << wLoader.fileName();

    Plugin* wPlugin = qobject_cast<Plugin*>(wLoader.instance());
    if(wPlugin) {
        qInfo() << "Plugin loaded: " << wPlugin->getVersion();
        wPlugin->writeFile(mapParseKeys, mapFileAttribs, outFile);
    }
}

void InputOutput::setData(QMap<QString, QString> parseKeys, QMap<QString, QString> fileAttribs, QString oFile)
{
    mapParseKeys = parseKeys;
    mapFileAttribs = fileAttribs;
    outFile = oFile;
}

void InputOutput::setpParser(QString pathToPlugin)
{
    pPluginPath = pathToPlugin;
}

void InputOutput::setwParser(QString pathToPlugin)
{
    wPluginPath = pathToPlugin;
}

void InputOutput::finished()
{
    //When Qt Concurrent is done
    qInfo() << this << "Processing...";
}
