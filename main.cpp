/**
 * @file main.cpp
 * @author ZHENG Robert (www.robert.hase-zheng.net)
 * @brief
 * @version 0.5.0
 * @date 2023-04-10
 *
 * @copyright Copyright (c) ZHENG Robert 2023
 *
 */

#include <QCoreApplication>

#include <iostream>
#include <QDir>
#include <QFile>

/* https://github.com/jarro2783/cxxopts */
#include "Includes/cxxopts.hpp"

#include "Includes/rz_inifile.h"
#include "Includes/rz_snippets.h"
#include "Includes/rz_dirfileinfo.h"


const std::string VERSION = "00.05.00";


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    std::string prog = argv[0];
    //QString file = prog.c_str();
    QString defaultInifile = prog.c_str();
    defaultInifile.append(".ini");
    QDir path = QDir::currentPath();
    QString dir = path.path();
    QMap<QString, QString> pluginParserMap;
    QMap<QString, QString> pluginWriterMap;

    Inifile Inifile;
    Snippets Snippets;

    cxxopts::Options options(prog, "file header parser");
    options
        .set_width(100)
        .add_options()
        ("c,create", "create Inifile")
        ("d,dir", "parse directory <dir>", cxxopts::value<std::string>())
        ("e,ext", "write to filetype (depends on Plugin):\n<.adoc> | <.csv> | <.html> | <.json> | <.md> | <.txt>", cxxopts::value<std::string>())
        ("f,file", "parse <pathTo/fileName>", cxxopts::value<std::string>())
        ("i,ini", "use Inifile <pathTo/inifile>", cxxopts::value<std::string>()->default_value(prog + ".ini"))
        ("l,listini", "list Inifile")
        ("o,out", "output directory <dir>", cxxopts::value<std::string>())
        ("v,version", "Print program and version")
        ("h, help", "Print help")
        ;

    auto result = options.parse(argc, argv);

    if (result.count("help")) {
        std::cout << options.help() << std::endl;
        exit(0);
    }
    if (result.count("version")) {
        std::cout << prog << "-" << VERSION << std::endl;
        exit(0);
    }

    // create default Inifile
    if (result.count("create")) {
        Inifile.createIni(dir);
        Snippets.checkBool(Inifile.saveIniToFile(dir, defaultInifile));
        exit(0);
    }

    // load given Inifile
    if (result.count("ini")) {
        std::string dirfile = result["ini"].as<std::string>();
        QString dirFile = dirfile.c_str();

        Snippets.checkBool(Inifile.loadIni(dirFile));
    } else {
        Snippets.checkBool(Inifile.loadIni(defaultInifile));
    }

    if(result.count("listini")) {
        Inifile.listIniEntries();
        exit(0);
    }

     // check confi
    Snippets.checkBool(Inifile.checkIniInputs());
    Snippets.checkBool(Inifile.checkIniMeta());
    Snippets.checkBool(Inifile.checkIniOutputs());
    // get + check plugins
    Snippets.checkBool(Inifile.checkIniPlugins(Snippets, pluginParserMap, pluginWriterMap));

    // request single file parsing?
    if(result.count("file")) {
        std::string dirfile = result["file"].as<std::string>();
        QString dirFile = dirfile.c_str();
        DirFileInfo df(dirFile);

        // test
        //df.listMapFileAttribs();
        for (QMap<QString, QString>::const_iterator it = df.mapFileAttribs.cbegin(), end = df.mapFileAttribs.cend(); it != end; ++it) {
            qInfo() << "key: " << it.key() << ": " << it.value();
        }
    }



    // the end
    exit(0);
    return a.exec();
}
