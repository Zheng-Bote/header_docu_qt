#include "rz_dofile.h"


DoFile::DoFile()
{

}

void DoFile::run()
{
    QPluginLoader pLoader(pPluginPath);
    if(!pLoader.load()) {
        qDebug() << "Error: " << pLoader.fileName() << " Error: " << pLoader.errorString();
        //return;
    }

    //qDebug() << "Loaded: " << pLoader.fileName();

    Plugin* pPlugin = qobject_cast<Plugin*>(pLoader.instance());
    if(pPlugin) {
        //qInfo() << "Plugin loaded: " << pPlugin->getVersion();
        pPlugin->parseFile(mapParseKeys, inFile);
    }

    QPluginLoader wLoader(wPluginPath);
    if(!wLoader.load()) {
        qDebug() << "Error: " << wLoader.fileName() << " Error: " << wLoader.errorString();
        //return;
    }

    //qDebug() << "Loaded: " << wLoader.fileName();

    Plugin* wPlugin = qobject_cast<Plugin*>(wLoader.instance());
    if(wPlugin) {
        //qInfo() << "Plugin loaded: " << wPlugin->getVersion();
        wPlugin->writeFile(mapParseKeys, mapFileAttribs, outFile);
    }
}
