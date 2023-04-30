/**
 * @file rz_header_docu_plugins.h
 * @author ZHENG Robert (www.robert.hase-zheng.net)
 * @brief interface library for header_docu and plugins
 * @details IID net.hase-zheng.header_docu_plugin
 * @version 0.2.0
 * @date 2023-04-15
 *
 * @copyright Copyright (c) ZHENG Robert 2023
 *
 */

#pragma once

#include <QMap>
#include <QString>
#include <QDebug>

class Plugin {
public:
    // virtual ~Plugin() = 0;
    virtual void test(QString name) = 0;
    virtual QString getName() = 0;
    virtual QString getVersion() = 0;

    virtual void parseFile(QMap<QString, QString> &mapParseKeys, QString pathToFile) = 0;
    virtual void writeFile(QMap<QString, QString> mapParseKeys, QMap<QString, QString> mapFileAttribs, QString pathToFile) = 0;

};

Q_DECLARE_INTERFACE(Plugin, "net.hase-zheng.header_docu_plugin");


