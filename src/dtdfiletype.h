#include "filetype.h"

#include "bong_qt_export.h"

class BONG_QT_EXPORT DTDFileType : public FileType
{
public:
    void readFile(QIODevice *inputFile, Translatable *translatable);
    void writeFile(QIODevice *outputFile, QString locale, Translatable *translatable);

protected:
    QString m_contents;
};
