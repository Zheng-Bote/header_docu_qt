#include "rz_inifile.h"

Inifile::Inifile()
{}

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

    try {
        myIni.save(pathFile.toStdString());
    } catch (...) {
        qWarning() << "Write Ini failed: " << pathFile;
        return false;
    }

    return true;
}

bool Inifile::loadIni(QString &pathFile)
{
    QFileInfo fi(pathFile);

    if(fi.exists() == false || fi.isReadable() == false) {
        qWarning() << "File doesn't exist or is not readable: " << pathFile;
        return false;
    }

    myIni.load(pathFile.toStdString());

    if(myIni.size() < 3) {
        qWarning() << "wrong INI size, should be 3 (maybe not readable?): " << myIni.size();
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

void Inifile::listIniEntries()
{
    std::cout << "Parsed ini contents" << std::endl;
    std::cout << "Has " << myIni.size() << " sections" << std::endl;
    for(const auto &sectionPair : myIni)
    {
        const std::string &sectionName = sectionPair.first;
        const ini::IniSection &section = sectionPair.second;
        std::cout << "Section '" << sectionName << "' has " << section.size() << " fields" << std::endl;

        for(const auto &fieldPair : sectionPair.second)
        {
            const std::string &fieldName = fieldPair.first;
            const ini::IniField &field = fieldPair.second;
            std::cout << "  Field '" << fieldName << "' Value '" << field.as<std::string>() << "'" << std::endl;
        }
    }
}

bool Inifile::checkIniInputs()
{
    std::string inputDir = myIni["Input"]["Dir"].as<std::string>();
    std::string inputExtensionsStr = myIni["Input"]["Extensions"].as<std::string>();


    // Input Dir
    if(inputDir.empty() == true){
        qWarning() << "No Input directory defined: " << inputDir;
        return false;
    }
    QDir dir(inputDir.c_str());
    if(dir.exists() == false) {
        qWarning() << "Input directory doesn't exist: " << inputDir;
        return false;
    }
    if(dir.isReadable() == false) {
        qWarning() << "Input directory is not readable: " << inputDir;
        return false;
    }
    if(dir.isEmpty(QDir:: NoDotAndDotDot | QDir::Files)) {
        qWarning() << "Input directory is empty: " << inputDir;
        return false;
    }

    // Extensions
    if(inputExtensionsStr.empty() == true) {
        qWarning() << "No Input extensions defined";
        return false;
    }

    // check for dir entries matching to extensions
    QString qextensionsStr = inputExtensionsStr.c_str();
    QStringList extensions = qextensionsStr.remove(" ").split(",");

    QFileInfoList list = dir.entryInfoList(extensions);
    if(list.isEmpty() == true) {
        qWarning() << "Input directory has no files with matching extension: " << list.length();
        return false;
    }
    /*
    foreach(QFileInfo file, list) {
        qInfo() << "file: " << file.path() << " : " << file.fileName();
    }
    */

    return true;
}

bool Inifile::checkIniMeta()
{
    std::string metaAttributes = myIni["Meta"]["Attributes"].as<std::string>();
    std::string metaMetadata = myIni["Meta"]["Metadata"].as<std::string>();

    // Attributes
    if(metaAttributes.empty() == true) {
        qWarning() << "No Meta attributes defined";
        return false;
    }

    // Metadata
    if(metaMetadata.empty() == true) {
        qWarning() << "No Meta metadata defined";
        return false;
    }
    return true;
}

bool Inifile::checkIniOutputs()
{
    std::string outDir = myIni["Output"]["Dir"].as<std::string>();
    std::string outFiletype = myIni["Output"]["Filetype"].as<std::string>();
    bool outSingleFile = false;
    try {
        outSingleFile = myIni["Output"]["singleFile"].as<bool>();
    } catch (...) {
        outSingleFile = false;
    }

    // Dir
    if(outDir.empty() == true) {
        qWarning() << "No Output dir defined";
        return false;
    }

    QDir dir(outDir.c_str());
    if(dir.exists() == false) {
        qWarning() << "Output dir doesn't exist: " << outDir;
        dir = QDir::root();
        if(dir.mkpath(outDir.c_str()) == false) {
            qWarning() << "Output dir not created";
            return false;
        } else {
            qInfo() << "Output dir created: " << outDir;
        }
    }

    // Filetype
    if(outFiletype.empty() == true) {
        qWarning() << "No Output filetype defined";
        return false;
    }

    return true;
}

bool Inifile::checkIniPlugins()
{
    std::string pluginsParserDir = myIni["Plugins"]["parserDir"].as<std::string>();
    std::string pluginsWriterDir = myIni["Plugins"]["writerDir"].as<std::string>();

    // pluginsParserDir
    if(pluginsParserDir.empty() == true) {
        qWarning() << "No Plugins ParserDir defined";
        return false;
    }
    QDir parserDir(pluginsParserDir.c_str());
    if(parserDir.exists() == false) {
        qWarning() << "Plugins ParserDir doesn't exist: " << pluginsParserDir;
        return false;
    }

    // pluginsWriterDir
    if(pluginsWriterDir.empty() == true) {
        qWarning() << "No Plugins WriterDir defined";
        return false;
    }
    QDir writerDir(pluginsWriterDir.c_str());
    if(writerDir.exists() == false) {
        qWarning() << "Plugins WriterDir doesn't exist: " << pluginsWriterDir;
        return false;
    }

    return true;
}

QString Inifile::getAttribs()
{
    std::string attribs = myIni["Meta"]["Attributes"].as<std::string>();
    return attribs.c_str();
}
