#pragma once

#include <QString>
#include <QDebug>

class Plugin {
public:
    // virtual ~Plugin() = 0;
    virtual void test(QString name) = 0;
    virtual QString getName() = 0;
    virtual void parseFile(QString pathToFile) = 0;
    virtual void writeFile(QString pathToFile) = 0;

};

Q_DECLARE_INTERFACE(Plugin, "net.hase-zheng.header_docu_plugin");


