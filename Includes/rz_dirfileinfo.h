#pragma once

#include <QCoreApplication>
#include <QDir>
#include <QFileInfo>
#include <QFileInfoList>
#include <QDateTime>
#include <QTimeZone>
#include <QMap>
#include <QCryptographicHash>
#include <QDebug>

#include "rz_datetime.h"

class DirFileInfo
{
public:
    DirFileInfo();
    DirFileInfo(QString &pathToFile);
    ~DirFileInfo();

    void cleanPathToFile(QString &pathToFile);

    void listMapFileAttribs();
    void addMapParseKeys(QStringList map_ParseKeys);

    rz_datetime::date_time dt;
    bool isFile{false};

    QMap<QString, QString> mapParseKeys{};
    QMap<QString, QString> mapFileAttribs{};

private:
    QString pathFile{}, path{}, permAlpha{}, permNumeric{};

    void setterFileInfo(const QFileInfo &fi);
    void setterDirInfo(QString &pathToFile);
    void setPermissions(QFileInfo &fi);
    void setDateTimeInfo(QFileInfo &fi);
    void setMapKeysInit();
    void setFileHashSHA256(QString &pathToFile);

    const QByteArray alphanumPerm(const QFileInfo &fi);
    int numericPerm(QFileInfo &fi);

};

