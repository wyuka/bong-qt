#include "filetype.h"

class DTDFileType : public FileType
{
public:
    void readFile(QString fileName, Translatable *translatable);
    void writeFile(QString fileName, QString locale, Translatable *translatable);

protected:
    QString m_contents;
};