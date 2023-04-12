#include "rz_dirfileinfo.h"

DirFileInfo::DirFileInfo()
{
    DirFileInfo::setMapKeysInit();
}

DirFileInfo::DirFileInfo(QString &pathToFile)
{
    QFileInfo fi(pathToFile);
    DirFileInfo::setMapKeysInit();

    if(fi.isDir()) {
        DirFileInfo::setterDirInfo(pathToFile);
    }
    if(fi.isFile()){
        DirFileInfo::setterFileInfo(fi);
    }

    DirFileInfo::setPermissions(fi);
    DirFileInfo::setDateTimeInfo(fi);
}

DirFileInfo::~DirFileInfo()
{
    mapFileAttribs.clear();
    mapParseKeys.clear();
}

void DirFileInfo::cleanPathToFile(QString &path)
{
    path = QDir::cleanPath(path);
}

void DirFileInfo::listMapFileAttribs()
{
    for (QMap<QString, QString>::const_iterator it = mapFileAttribs.cbegin(), end = mapFileAttribs.cend(); it != end; ++it) {
        qInfo() << "key: " << it.key() << ": " << it.value();
    }
}

void DirFileInfo::setterFileInfo(const QFileInfo &fi)
{
    mapFileAttribs["FILE_Name"] = fi.fileName();
    mapFileAttribs["FILE_completeSuffix"] = fi.completeSuffix();
    mapFileAttribs["FILE_baseFileName"] = fi.baseName();
    pathFile = QDir::cleanPath(fi.filePath());
    path = fi.absolutePath();
    QFileInfo dirinfo(path);
    mapFileAttribs["FILE_baseDirName"] = dirinfo.baseName();
    mapFileAttribs["FILE_Size"] = QString::number(fi.size());
    isFile = true;
}

void DirFileInfo::setterDirInfo(QString &pathToFile)
{
    path = QDir::cleanPath(pathToFile);
    QFileInfo dirinfo(path);
    mapFileAttribs["FILE_baseDirName"] = dirinfo.baseName();
}

void DirFileInfo::setPermissions(QFileInfo &fi)
{
    DirFileInfo::alphanumPerm(fi);
    DirFileInfo::numericPerm(fi);
}

void DirFileInfo::setDateTimeInfo(QFileInfo &fi)
{
    mapFileAttribs["FILE_created_localtime"] = fi.birthTime().toString("yyyy-MM-dd HH:mm:ss");
    mapFileAttribs["FILE_LastModified_localtime"] = fi.lastModified().toString("yyyy-MM-dd HH:mm:ss");

    QDateTime UTCcurrent(QDateTime::currentDateTimeUtc());
    QDateTime local(UTCcurrent.toLocalTime());

    mapFileAttribs["FILE_Scan_UTCcurrent"] = dt.UTCcurrent = UTCcurrent.toString("yyyy-MM-dd HH:mm:ss");
    mapFileAttribs["FILE_Scan_localTime"] = dt.localTime = local.toString("yyyy-MM-dd HH:mm:ss");

    QDateTime UTC(fi.lastModified().toUTC());
    QTimeZone tz = fi.lastModified().timeZone();
    mapFileAttribs["FILE_lastModified_humanUTC"] = dt.humanUTC = UTC.toString("yyyy-MM-dd HH:mm:ss");
    mapFileAttribs["FILE_lastModified_stringUTC"] = dt.stringUTC = UTC.toString("yyyy-MM-dd_HH-mm-ss");
    mapFileAttribs["FILE_lastModified_timeUTC"] = dt.timeUTC = UTC.toString("yyyy-MM-ddTHH:mm:ssZ");
    mapFileAttribs["FILE_lastModified_timeUtcOffset"] = dt.timeUtcOffset = tz.displayName(fi.lastModified(),QTimeZone::OffsetName); // "UTC+02:00"
    mapFileAttribs["FILE_lastModified_timeZAbbreviation"] = dt.timeZAbbreviation = fi.lastModified().timeZoneAbbreviation(); // "CEST"

/*
    spdxTimeUtcOffset = tz.displayName(fi.lastModified(),QTimeZone::OffsetName); // spdx time:  "UTC+02:00"
    spdxTimeZAbbreviation = fi.lastModified().timeZoneAbbreviation(); // spdx time:  "CEST"
    spdxTimeUTC = UTC.toString("yyyy-MM-ddTHH:mm:ssZ");
*/
}

void DirFileInfo::setMapKeysInit()
{
    mapParseKeys = {
        {"FILE",""}, {"TITLE", ""}, {"AUTHOR", ""}, {"BRIEF", ""},
        {"VERSION", ""}, {"DATE",""}, {"DESC", ""}, {"DESCRIPTION", ""},
        {"LICENSE", ""}, {"COPYRIGHT", ""},
        {"SOURCE", ""}, {"COMMENT", ""}, {"SYNTAX", ""},
        {"DEPENDENCIES", ""}, {"HISTORY", ""}
    };

    mapFileAttribs = {
        {"FILE_Name",""}, {"FILE_baseFileName",""}, {"FILE_completeSuffix",""}, {"FILE_baseDirName",""},
        {"FILE_created_localtime", ""}, {"FILE_LastModified_localtime",""},
        {"FILE_lastModified_humanUTC",""}, {"FILE_lastModified_stringUTC", ""},
        {"FILE_lastModified_timeUTC",""}, {"FILE_lastModified_timeUtcOffset",""},
        {"FILE_lastModified_timeZAbbreviation",""},
        {"FILE_Perm_Numeric", ""}, {"FILE_Perm_AlphaNumeric", ""},
        {"FILE_Size", ""}, {"FILE_SHA256_Hash", ""},
        {"FILE_Scan_localTime",""}, {"FILE_Scan_UTCcurrent",""}
    };
}

const QByteArray DirFileInfo::alphanumPerm(const QFileInfo &fi)
{
    QByteArray ret(fi.isDir()?"d":"-");
    ret += (fi.permission(QFile::ReadOwner))?"r":"-";
    ret += (fi.permission(QFile::WriteOwner))?"w":"-";
    ret += (fi.permission(QFile::ExeOwner))?"x":"-";
    ret += (fi.permission(QFile::ReadGroup))?"r":"-";
    ret += (fi.permission(QFile::WriteGroup))?"w":"-";
    ret += (fi.permission(QFile::ExeGroup))?"x":"-";
    ret += (fi.permission(QFile::ReadOther))?"r":"-";
    ret += (fi.permission(QFile::WriteOther))?"w":"-";
    ret += (fi.permission(QFile::ExeOther))?"x":"-";

    mapFileAttribs["FILE_Perm_AlphaNumeric"] = permAlpha = ret.toStdString().c_str();

    return ret;
}

int DirFileInfo::numericPerm(QFileInfo &fi)
{
    int p = 0;

    if (fi.permission(QFile::ReadUser))
        p += 400;
    if (fi.permission(QFile::WriteUser))
        p += 200;
    if (fi.permission(QFile::ExeUser))
        p += 100;
    if (fi.permission(QFile::ReadGroup))
        p += 40;
    if (fi.permission(QFile::WriteGroup))
        p += 20;
    if (fi.permission(QFile::ExeGroup))
        p += 10;
    if (fi.permission(QFile::ReadOther))
        p += 4;
    if (fi.permission(QFile::WriteOther))
        p += 2;
    if (fi.permission(QFile::ExeOther))
        p += 1;

    mapFileAttribs["FILE_Perm_Numeric"] = permNumeric = QString::number(p);
    return p;
}

