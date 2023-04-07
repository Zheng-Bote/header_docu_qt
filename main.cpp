#include <QCoreApplication>

#include <iostream>
#include <QDir>
#include <QFile>

/* https://github.com/jarro2783/cxxopts */
#include "Includes/cxxopts.hpp"

/* https://github.com/Rookfighter/inifile-cpp */
#include "Includes/inicpp.h"


const std::string VERSION = "00.01.00";

bool createIni(ini::IniFile &myIni, QString &path, QString &file) {

    QString pathFile = path + "/" + file + ".ini";

    myIni["Plugins"]["parserDir"] = path.toStdString() + "/Plugins/parser";
    myIni["Plugins"]["writerDir"] = path.toStdString() + "/Plugins/writer";

    myIni["Input"]["Dir"] = path.toStdString() + "/Inputs";
    myIni["Input"]["Extensions"] = ".h, .hpp, .c, .cpp";

    myIni["Meta"]["Metadata"] = "TITLE, BRIEF, DESC, AUTHOR, LICENSE, VERSION, COPYRIGHT, SOURCE, COMMENT, SYNTAX, HISTORY, DEPENDENCIES";
    myIni["Meta"]["Attributes"] = "FILE_PERM, LAST_MODIFIED, FILE_SIZE, FILE_HASH_SHA256";

    myIni["Output"]["Dir"] = path.toStdString() + "/Outputs";
    myIni["Output"]["Filetype"] = ".txt";
    myIni["Output"]["singleFile"] = false;



    myIni.save(pathFile.toStdString());

    qInfo() << "Inifile: " << pathFile;
    QFile qFile = path + "/" + file;
    if(qFile.exists() == false) {
        qFatal() << "File doesn't exist: " << qFile.fileName();
        return false;
    } else {
        return true;
    }
}

bool loadIni(ini::IniFile &myIni, QString &pathFile) {

    QFile qFile = pathFile;

    if(qFile.exists() == false) {
        qFatal() << "File doesn't exist: " << qFile.fileName();
        return false;
    }

    myIni.load(pathFile.toStdString());

    if(myIni.size() < 3) {
        qFatal() << "wrong INI size, should be 3 (maybe not readable?): " << myIni.size();
        return false;
    }

    /* just 4 testing
    QStringList extensions{};
    bool singleFile = false;

    std::string inputDir = myIni["Input"]["Dir"].as<std::string>();
    std::string outputDir = myIni["Output"]["Dir"].as<std::string>();
    std::string outPutExtension = myIni["Output"]["Extension"].as<std::string>();
    singleFile = myIni["Output"]["singleFile"].as<bool>();
    std::string parserDir = myIni["Plugins"]["parserDir"].as<std::string>();
    std::string writerDir = myIni["Plugins"]["writer"].as<std::string>();
    std::string extensionsStr = myIni["Input"]["Extensions"].as<std::string>();

    QString qextensionsStr = extensionsStr.c_str();
    extensions = qextensionsStr.remove(" ").split(",");
    foreach (const QString &str, extensions) {
        qInfo() << "Item: " << str;
    }
    */

    return true;
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    std::string prog = argv[0];
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

    ini::IniFile myIni;
    QDir path{};

    QString dir = path.path();
    QString file{};

    if (result.count("create"))
    {
        dir = QDir::currentPath();
        file = prog.c_str();

        qInfo() << "option c";

        if(createIni(myIni, dir, file)) {
            qInfo() << "ini created";
            exit(0);
        } else {
            qFatal() << "failed to create ini";
            exit(1);
        }
    }

    if (result.count("ini"))
    {
        std::string dirfile = result["ini"].as<std::string>();
        QString dirFile = dirfile.c_str();

        if(! loadIni(myIni, dirFile)) {
            qFatal() << "Ini NOT loaded, program aborted";
            exit(1);
        } else {
            qInfo() << "ini loaded: " << dirFile;
        }
    }

    exit(0);
    return a.exec();
}
