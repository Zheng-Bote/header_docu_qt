#pragma once

#include <QCoreApplication>

#include <QObject>
#include <QFuture>
#include <QFutureWatcher>
#include <QtConcurrent>
#include <QThread>
#include <QThreadPool>
#include <QPluginLoader>

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

private:
    QMap<QString, QString> mapParseKeys;
    QMap<QString, QString> mapFileAttribs;
    QString inFile, outFile{};
    QString wPluginPath{}, pPluginPath{};

signals:

public slots:
    void finished();


};
