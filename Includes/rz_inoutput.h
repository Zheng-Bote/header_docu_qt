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

    void setData(QMap<QString, QString> mapParseKeys, QMap<QString, QString> mapFileAttribs, QString outFile="/media/zb_bamboo/500GB/Dev/QT/build-header_docu_qt-Desktop_Qt_6_5_0_GCC_64bit-Debug/Outputs/test.json");
    void setpParser(QString pathToPlugin);
    void setwParser(QString pathToPlugin);

private:
    QMap<QString, QString> mapParseKeys;
    QMap<QString, QString> mapFileAttribs;
    QString outFile{};
    QString wPluginPath{}, pPluginPath{};

signals:

public slots:
    void finished();


};
