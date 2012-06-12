#include "translatable.h"
#include "propertiesfiletype.h"
#include <iostream>

using namespace std;

int main1(int argc, char* argv[])
{
    FileType *fileType = new PropertiesFileType();
    Translatable *translatable = new Translatable(fileType);

    translatable->addEntry("I love you", 0, QString(), "en", "I love you");
    translatable->addEntry("I love you", 0, QString(), "bn", "আমি তোমায় ভালোবাসি");
    translatable->addEntry("I love you", 0, QString(), "hi", "मैं तुमसे प्यार करता हूँ");
    translatable->addEntry("I like you", 1, QString(), "en", "I like you");
    translatable->addEntry("I like you", 1, QString(), "bn", "আমার তোমাকে ভালো লাগে");
    translatable->addEntry("I like you", 1, QString(), "hi", "मैं तुम्हें पसंद करता हूँ");

    cout << translatable->findString("I love you", "en").length() << endl;
    cout << translatable->findString("I love you", "bn").length() << endl;
    cout << translatable->findString("I love you", "hi").length() << endl;

    cout << translatable->findString(1, "en").length() << endl;
    cout << translatable->findString(1, "bn").length() << endl;
    cout << translatable->findString(1, "hi").length() << endl;

    cout << translatable->findUik(0).length() << endl;
    cout << translatable->findEntryIndex("I love you") << endl;
    cout << translatable->findUik(1).length() << endl;
    cout << translatable->findEntryIndex("I like you") << endl;

    delete translatable;
    return 0;
}