#ifndef DOFILE_H
#define DOFILE_H

#include <QCoreApplication>
#include <QObject>

#include <QPluginLoader>
#include <QDir>
#include <QFileInfo>

#include <QRunnable>
#include <QThread>

#include "rz_header_docu_plugins.h"

class DoFile : public QRunnable
{

public:
    DoFile();

    void run();

    QMap<QString, QString> mapParseKeys;
    QMap<QString, QString> mapFileAttribs;
    QString inFile, outFile;
    QString wPluginPath;
    QString pPluginPath;
};

#endif // DOFILE_H
