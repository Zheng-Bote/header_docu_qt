/**
 * @file hd_ghmd_writer_plugin.cpp
 * @author ZHENG Robert (www.robert.hase-zheng.net)
 * @brief Github markdown writer plugin for header_docu
 * @details write Github Markdown header
 * @version 0.1.0
 * @date 2023-04-22
 *
 * @copyright Copyright (c) ZHENG Robert 2023
 *
 */

#include "hd_ghmd_writer_plugin.h"

const QString PLUGIN_SHORTNAME = "gh_markdown";
const QString PLUGIN_NAME ="Github Markdown writer";
const QString PLUGIN_VERSION = "0.1.0";

Hd_ghmd_writer_plugin::Hd_ghmd_writer_plugin(QObject *parent)
{
    Q_UNUSED(parent);
    qInfo() << "Plugin Constructor";
}

Hd_ghmd_writer_plugin::~Hd_ghmd_writer_plugin()
{
    qInfo() << "Plugin Deconstructed";
}

void Hd_ghmd_writer_plugin::test(QString name)
{
    qInfo() << "Test from Plugin: " << PLUGIN_SHORTNAME << ": " << name;
}

QString Hd_ghmd_writer_plugin::getName()
{
    return PLUGIN_SHORTNAME;
}

QString Hd_ghmd_writer_plugin::getVersion()
{

}

void Hd_ghmd_writer_plugin::parseFile(QMap<QString, QString> &mapParseKeys, QString pathToFile)
{

}

void Hd_ghmd_writer_plugin::writeFile(QMap<QString, QString> mapParseKeys, QMap<QString, QString> mapFileAttribs, QString pathToFile)
{

}
