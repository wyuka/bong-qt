#include "translatable.h"
#include "propertiesfiletype.h"
#include <iostream>

using namespace std;

int main2(int argc, char* argv[])
{
    FileType *fileType = new PropertiesFileType();
    Translatable *translatable = new Translatable(fileType);

    if (argc < 3)
        return 1;

    translatable->readFile(argv[1]);
    /*int k = translatable->entryCount();
    for (int i = 0; i < k; i++)
    {
        cout << qPrintable(translatable->findUik(i)) << " = ";
        cout << qPrintable(translatable->findString(i, "en")) << endl;
        cout << qPrintable(translatable->findNote(i)) << endl << endl;
    }*/

    translatable->addEntry("cmd_showSuggestions", -1, QString(), "en", "suggestions dekhan");
    translatable->writeFile(argv[2], "en");

    delete translatable;
    return 0;
}