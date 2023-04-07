#include "rz_inifile.h"

RZ_Inifile::RZ_Inifile()
{

}

ini::IniFile RZ_Inifile::createInstance() {
    ini::IniFile myIni;
    return myIni;
}

bool RZ_Inifile::createIni(ini::IniFile &myIni, QString path, QString file)
{
    QString pathFile = path + "/" + file;

    myIni["Plugins"]["parserDir"] = path.toStdString() + "/Plugins/parser";
    myIni["Plugins"]["writerDir"] = path.toStdString() + "/Plugins/writer";

    myIni["Input"]["Dir"] = path.toStdString() + "/Inputs";
    myIni["Input"]["Extensions"] = ".h, .hpp, .c, .cpp";

    myIni["Output"]["Dir"] = path.toStdString() + "/Outputs";
    myIni["Output"]["Extension"] = ".txt";
    myIni["Output"]["singleFile"] = false;

    myIni.save(pathFile.toStdString());
    qInfo() << "Inifile: " << pathFile;

    QFile qFile = pathFile;
    if(qFile.exists() == false) {
        qFatal() << "File doesn't exist: " << qFile.fileName();
        return false;
    }
    else {
        return true;
    }
}

bool RZ_Inifile::loadIni(ini::IniFile &myIni, QString &path, QString &file)
{
    QFile qFile = path + "/" + file;

    if(qFile.exists() == false) {
        qFatal() << "File doesn't exist: " << qFile.fileName();
        return false;
    }

    myIni.load(path.toStdString() + "/" + file.toStdString());

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
