#pragma once

#include <QCoreApplication>

#include <QObject>

#include <QPluginLoader>
#include <QDir>
#include <QFileInfo>

#include "rz_header_docu_plugins.h"

class InputOutput : public QObject
{
    Q_OBJECT

public:
    explicit InputOutput(QObject *parent = nullptr);
    ~InputOutput();

    static void run();
    //QThreadPool pool;
    void runner();

    void setData(QMap<QString, QString> mapParseKeys, QMap<QString, QString> mapFileAttribs);
    void setFiles(QString inFile, QString outFile);
    void setpParser(QString pathToPlugin);
    void setwParser(QString pathToPlugin);

    QString setOutputDir(QString inputPath, QString outputPath, QString FILE_absolutePath);

    void makeOutputDir(QString outputDir);

private:
    QMap<QString, QString> mapParseKeys;
    QMap<QString, QString> mapFileAttribs;
    QString inFile, outFile;
    QString wPluginPath, pPluginPath;

signals:

public slots:
    void finished();


};
