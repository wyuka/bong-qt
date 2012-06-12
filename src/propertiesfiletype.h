#include "filetype.h"

class PropertiesFileType : public FileType
{
public:
    void readFile(QString fileName, Translatable *translatable);
    void writeFile(QString fileName, QString locale, Translatable *translatable);

protected:
    QStringList m_lineList;
};