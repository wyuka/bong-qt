#ifndef FILETYPE_H
#define FILETYPE_H

#include <QtCore>
#include "translatable.h"

#include "bong_qt_export.h"

class BONG_QT_EXPORT FileType
{
public:
    virtual ~FileType() {};
    virtual void readFile(QIODevice *inputFile, Translatable* translatable) = 0;
    virtual void writeFile(QIODevice *outputFile, QString locale, Translatable* translatable) = 0;
};

#endif //FILETYPE_H
