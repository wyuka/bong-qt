#include "filetype.h"

#include "bong_qt_export.h"

class BONG_QT_EXPORT PropertiesFileType : public FileType
{
public:
    void readFile(QIODevice *inputFile, Translatable *translatable);
    void writeFile(QIODevice *outputFile, QString locale, Translatable *translatable);

protected:
    QStringList m_lineList;
};
