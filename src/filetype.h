#ifndef FILETYPE_H
#define FILETYPE_H

#include <QtCore>
#include <translatable.h>

class FileType
{
public:
    virtual void readFile(QString inputFile, Translatable* translatable) = 0;
    virtual void writeFile(QString inputFile, QString locale, Translatable* translatable) = 0;
};

#endif //FILETYPE_H