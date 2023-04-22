#ifndef HD_GHMD_WRITER_PLUGIN_H
#define HD_GHMD_WRITER_PLUGIN_H

#include <QObject>
#include <QtPlugin>
#include <QDebug>
#include <QString>

#include "rz_header_docu_plugins.h"

class Hd_ghmd_writer_plugin : public QObject, public Plugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "net.hase-zheng.header_docu_plugin");
    Q_INTERFACES(Plugin);

public:
    explicit Hd_ghmd_writer_plugin(QObject *parent = nullptr);
    ~Hd_ghmd_writer_plugin();

private:

signals:
public slots:

    // Plugin interface
public:
    void test(QString name) Q_DECL_OVERRIDE;
    QString getName() Q_DECL_OVERRIDE;
    QString getVersion() Q_DECL_OVERRIDE;

    void parseFile(QMap<QString, QString> &mapParseKeys, QString pathToFile) Q_DECL_OVERRIDE;
    void writeFile(QMap<QString, QString> mapParseKeys, QMap<QString, QString> mapFileAttribs, QString pathToFile) Q_DECL_OVERRIDE;
};

#endif // HD_GHMD_WRITER_PLUGIN_H
