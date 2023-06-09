/**
 * @file main.cpp
 * @author ZHENG Robert (www.robert.hase-zheng.net)
 * @brief header_docu
 * @details fileheader parser for documentation with parser plugins and output writer plugins
 * @version 1.3.0
 * @date 2023-04-30
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

#include "Includes/rz_datetime.h"
#include "Includes/rz_dirfileinfo.h"
#include "Includes/rz_inifile.h"
#include "Includes/rz_inoutput.h"
#include "Includes/rz_snippets.h"

const std::string VERSION = "01.03.00";

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    std::string prog = argv[0];
    QDir path = QDir::currentPath();
    QString dir = path.path();

    DateTime datetime;
    datetime.setDateTime();

    QMap<QString, QString> pluginParserMap;
    QMap<QString, QString> pluginWriterMap;

    //Inifile;
    QString pathToInifile = prog.c_str();
    pathToInifile.append(".ini");
    QString inputDir, outputDir, fileExtension, fileInType, fileOutType;

    Inifile Inifile;
    Snippets Snippets;

    cxxopts::Options options(prog, "file header parser");
    options.set_width(100)
        .add_options()("a,auto",
                       "run with default Inifile")("c,create",
                                                   "create Inifile")("d,dir",
                                                                     "parse directory <dir>",
                                                                     cxxopts::value<std::string>())(
            "e,ext",
            "file extension to search for. E.g.:\n<*.h> | <*.hpp> | <*.c> | <*.cpp>",
            cxxopts::value<std::string>())("f,file",
                                           "parse <pathTo/fileName>",
                                           cxxopts::value<std::string>())(
            "i,ini",
            "use Inifile <pathTo/inifile>",
            cxxopts::value<std::string>()->default_value(
                prog + ".ini"))("l,listini", "list Inifile (optional with --ini <pathTo/IniFile>)")(
            "o,out",
            "output directory <dir>",
            cxxopts::value<std::string>())("p,parser",
                                           "how to parse the input (use --plugins to list "
                                           "available plugins):\ne.g.: <gh_markdown> | <doxygen>",
                                           cxxopts::value<std::string>())("plugins",
                                                                          "list available plugins")(
            "w,writer",
            "output type (use --plugins to list "
            "available plugins):\ne.g.: <adoc> | <csv> | <html> | <json> | <md> | <txt>",
            cxxopts::value<std::string>())("v,version", "Print program and version")("h, help",
                                                                                     "Print help");

    auto result = options.parse(argc, argv);

    if (argc <= 1 || result.count("help")) {
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
        Snippets.checkBool(Inifile.saveIniToFile(dir, pathToInifile));
        exit(0);
    }

    // load given Inifile
    if (result.count("ini")) {
        std::string dirfile = result["ini"].as<std::string>();
        pathToInifile = dirfile.c_str();

        Snippets.checkBool(Inifile.loadIni(pathToInifile));
    }
    else {
        // load default Inifile
        //qInfo() << "load default Ini: " << pathToInifile;
        Snippets.checkBool(Inifile.loadIni(pathToInifile));
    }

    // list ini
    if(result.count("listini")) {
        Inifile.listIniEntries();
        exit(0);
    }

    // input dir
    if(result.count("dir")) {
        Inifile.setInputDir(result["dir"].as<std::string>());
    }

    // file extension
    if(result.count("ext")) {
        Inifile.setInputDir(result["ext"].as<std::string>());
    }

    // parse single file
    if(result.count("file")) {
        Inifile.setInputDir(result["file"].as<std::string>());
    }

    // output dir
    if(result.count("out")) {
        Inifile.setOutputDir(result["out"].as<std::string>());
    }

    // input type
    if(result.count("parser")) {
        Inifile.setParserType(result["parser"].as<std::string>());
        std::string fileintype = result["parser"].as<std::string>();
        fileInType = fileintype.c_str();
    } else {
        fileInType = Inifile.getParserType();
    }

    // output type => deprecated -> writer
    if(result.count("type")) {
        Inifile.setFileType(result["type"].as<std::string>());
        Inifile.setWriterType(result["type"].as<std::string>());
        std::string fileoutputtype = result["type"].as<std::string>();
        fileOutType = fileoutputtype.c_str();
    }
    // output type
    if(result.count("writer")) {
        Inifile.setWriterType(result["writer"].as<std::string>());
        std::string fileoutputtype = result["writer"].as<std::string>();
        fileOutType = fileoutputtype.c_str();
    } else {
        fileOutType = Inifile.getWriterType();
    }

    // list plug-ins
    if (result.count("plugins")) {
        qInfo() << "Parser Plug-Ins:\n================";
        QString pluginsDir = Inifile.getParserPluginsDir();
        Snippets.listPlugins(Snippets.getPlugins(pluginsDir));
        qInfo() << "\nWriter Plug-Ins:\n================";
        pluginsDir = Inifile.getWriterPluginsDir();
        Snippets.listPlugins(Snippets.getPlugins(pluginsDir));
        exit(0);
    }

    qInfo() << datetime.getHumanUTC() << " : " << prog << "-" << VERSION << " started";

    // check config
    Snippets.checkBool(Inifile.checkIniInputs());
    Snippets.checkBool(Inifile.checkIniMeta());
    Snippets.checkBool(Inifile.checkIniOutputs());
    // get + check plugins
    Snippets.checkBool(Inifile.checkIniPlugins(Snippets, pluginParserMap, pluginWriterMap));
    // check given plugin
    if(pluginParserMap.contains(fileInType) == false) {
        qWarning() << "no parser plug-in for input format " << fileInType << " found.";
        exit(1);
    }
    if(pluginWriterMap.contains(fileOutType) == false) {
        qWarning() << "no writer plug-in for output format " << fileOutType << " found.";
        exit(1);
    }


    //#######
    // request single file parsing?
    if(result.count("file")) {
        inputDir = Inifile.getInputDir();
        DirFileInfo df(inputDir);
        df.addMapParseKeys(Inifile.getMetadata());
        InputOutput* ioSingle = new InputOutput();
        ioSingle->setpParser(pluginParserMap[fileInType]);
        ioSingle->setwParser(pluginWriterMap[fileOutType]);
        ioSingle->setData(df.mapParseKeys,df.mapFileAttribs);

        //QString outPutFile = Inifile.getOutputDir() + "/" + df.mapFileAttribs["FILE_Name"] + "." + fileOutType;
        QString outPutFile = ioSingle->setOutputDir(Inifile.getInputDir(), Inifile.getOutputDir(), df.mapFileAttribs["FILE_absolutePath"]);
        //qInfo() << "\n\ntarget: " << outPutFile;
        ioSingle->makeOutputDir(outPutFile);
        outPutFile.append("/" + df.mapFileAttribs["FILE_baseFileName"] + "." + fileOutType);
        //qInfo() << "target file: " << outPutFile;
        Snippets.setCountedFiles(1);
        ioSingle->setFiles(Inifile.getInputDir(), outPutFile);
        ioSingle->runner();
    }

    // request parse dir
    if(result.count("dir")) {

        QDir dir = Inifile.getInputDir();
        inputDir = Inifile.getInputDir();
        outputDir = Inifile.getOutputDir();
        QStringList filters = Inifile.getInputExtensions();
        //Snippets.getDirsRecursive(dir, filters, pluginParserMap[fileInType], pluginWriterMap[fileOutType]);
        Snippets.getDirsRecursive(dir,
                                  inputDir,
                                  outputDir,
                                  filters,
                                  pluginParserMap[Inifile.getParserType()],
                                  pluginWriterMap[Inifile.getWriterType()],
                                  fileOutType,
                                  Inifile.getMetadata());
    }

    if (result.count("auto")) {
        QDir dir = Inifile.getInputDir();
        inputDir = Inifile.getInputDir();
        outputDir = Inifile.getOutputDir();
        QStringList filters = Inifile.getInputExtensions();
        //Snippets.getDirsRecursive(dir, filters, pluginParserMap[fileInType], pluginWriterMap[fileOutType]);
        Snippets.getDirsRecursive(dir,
                                  inputDir,
                                  outputDir,
                                  filters,
                                  pluginParserMap[Inifile.getParserType()],
                                  pluginWriterMap[Inifile.getWriterType()],
                                  fileOutType,
                                  Inifile.getMetadata());
    }

    /*
    // ##### TEST #####
    qInfo() << "##### Test von Main #####";
    QThread::currentThread()->setObjectName("Main");
    qInfo() << "Main: " << QThread::currentThread();
    QThreadPool pool;
    qInfo() << pool.maxThreadCount() << "Threads";
    QFutureWatcher<void> watcher;

    //InputOutput gh_markdown;
    InputOutput* gh_markdown = new InputOutput();
    //gh_markdown.run();
    QObject::connect(&watcher, &QFutureWatcher<void>::finished,gh_markdown,&InputOutput::run); //Auto connect "should" work


    //QFuture<void> future = QtConcurrent::map(list,&multiply);
    QFuture<void> future = QtConcurrent::run(&pool, gh_markdown->run);
    watcher.setFuture(future);

    qInfo() << "Back in main!";

    watcher.waitForFinished(); //Blocking
*/

    datetime.setDateTime();

    // 2023-04-03 18:22:57 : Snippets.getCountedFiles() .cpp Files in folder ./src found. Output stored with format md in folder ./header_docu_cpp
    qInfo() << datetime.getHumanUTC() << " : "
            << "File(s) parsed with " << fileInType << " header parser. Output stored with format "
            << fileOutType << " in folder: " << Inifile.getOutputDir();

    // the end
    exit(0);
    return a.exec();
}

