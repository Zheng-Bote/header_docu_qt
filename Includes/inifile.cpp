#include "inifile.h"

Inifile::Inifile()
{
    QString dir = QDir::currentPath();
    createIni(dir);
}

Inifile::Inifile(QString &progname)
{
    QDir path = QDir::currentPath();
    QString dir = path.path();
    QString file = progname + ".ini";
    createIni(dir);
    saveIniToFile(dir, file);
}

Inifile::Inifile(QString &path, QString &file)
{
    createIni(path);
    saveIniToFile(path, file);
}

Inifile::~Inifile()
{

}

void Inifile::Test()
{

}

void Inifile::createIni(QString &path)
{
    myIni["Plugins"]["parserDir"] = path.toStdString() + "/Plugins/parser";
    myIni["Plugins"]["writerDir"] = path.toStdString() + "/Plugins/writer";

    myIni["Input"]["Dir"] = path.toStdString() + "/Inputs";
    myIni["Input"]["Extensions"] = ".h, .hpp, .c, .cpp";

    myIni["Meta"]["Metadata"] = "TITLE, BRIEF, DESC, AUTHOR, LICENSE, VERSION, COPYRIGHT, SOURCE, COMMENT, SYNTAX, HISTORY, DEPENDENCIES";
    myIni["Meta"]["Attributes"] = "FILE_PERM, LAST_MODIFIED, FILE_SIZE, FILE_HASH_SHA256";

    myIni["Output"]["Dir"] = path.toStdString() + "/Outputs";
    myIni["Output"]["Filetype"] = ".txt";
    myIni["Output"]["singleFile"] = false;
}

bool Inifile::saveIniToFile(QString &path, QString &file)
{
    QString pathFile = path + "/" + file;
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

bool Inifile::loadIni(QString &pathFile)
{
    QFile qFile = pathFile;

    // shitty
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

    std::string attribs = myIni["Meta"]["Attributes"].as<std::string>();
    qInfo() << "Atributes: " << attribs;
    QString qextensionsStr = extensionsStr.c_str();
    extensions = qextensionsStr.remove(" ").split(",");
    foreach (const QString &str, extensions) {
        qInfo() << "Item: " << str;
    }
*/
    return true;
}

QString Inifile::getAttribs()
{
    std::string attribs = myIni["Meta"]["Attributes"].as<std::string>();
    return attribs.c_str();
}
