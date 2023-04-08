#include <QCoreApplication>

#include <iostream>
#include <QDir>
#include <QFile>

/* https://github.com/jarro2783/cxxopts */
#include "Includes/cxxopts.hpp"



#include "Includes/inifile.h"


const std::string VERSION = "00.02.00";


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    // create default ini
    std::string prog = argv[0];
    QString file = prog.c_str();
    Inifile Inifile;

    cxxopts::Options options(prog, "file header parser");
    options
        .set_width(100)
        .add_options()
        ("c,create", "create Inifile")
        ("d,dir", "parse directory <dir>")
        ("e,ext", "write to filetype (depends on Plugin):\n<.adoc> | <.csv> | <.html> | <.json> | <.md> | <.txt>", cxxopts::value<std::string>())
        ("f,file", "parse <pathTo/fileName>", cxxopts::value<std::string>())
        ("i,ini", "use Inifile <pathTo/inifile>", cxxopts::value<std::string>()->default_value(prog + ".ini"))
        ("o,out", "output directory <dir>")
        ("v,version", "Print program and version")
        ("h, help", "Print help")
        ;

    auto result = options.parse(argc, argv);

    if (result.count("help"))
    {
        std::cout << options.help() << std::endl;
        exit(0);
    }
    if (result.count("version"))
    {
        std::cout << prog << "-" << VERSION << std::endl;
        exit(0);
    }

    /* create default Inifile */
    if (result.count("create"))
    {
        QDir path = QDir::currentPath();
        QString dir = path.path();
        QString file = prog.c_str();
        file.append(".ini");
        // we got already a default ini in memory, just safe it to disk
        Inifile.saveIniToFile(dir, file);
    }

    /* load given Inifile */
    if (result.count("ini"))
    {
        std::string dirfile = result["ini"].as<std::string>();
        QString dirFile = dirfile.c_str();

        if(! Inifile.loadIni(dirFile)) {
            qFatal() << "Ini NOT loaded, program aborted";
            exit(1);
        } else {
            qInfo() << "ini loaded: " << dirFile;
        }

    }

    exit(0);
    return a.exec();
}
