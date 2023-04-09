#include "rz_snippets.h"


Snippets::Snippets()
{}

void Snippets::checkBool(const bool &boolCheck)
{
    if(boolCheck == false) {
        qCritical() << "program criterias missmatch";
        exit(1);
    }
}

