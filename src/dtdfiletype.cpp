#include <dtdfiletype.h>
#include <QtCore>

void DTDFileType::readFile(QString fileName, Translatable *translatable)
{
    QFile file(fileName);
    file.open(QFile::ReadOnly);
    QTextStream textStream(&file);
    m_contents = textStream.readAll();
    QString key, value;
    QRegExp entityRx("<!ENTITY (.*)\\s*\"(.*)\">", Qt::CaseSensitive, QRegExp::RegExp2);
    entityRx.setMinimal(true);
    int pos = 0;
    int i = 0;

    while ((pos = entityRx.indexIn(m_contents, pos)) != -1) {
        key = entityRx.cap(1).trimmed();
        value = entityRx.cap(2);
        translatable->addEntry(key, i++, QString(), "en", value);
        pos += entityRx.matchedLength();
    }


    QStringList noteKeyList;
    QString noteValue;
    QRegExp noteRx("<!--\\s*LOCALIZATION NOTE\\s*(.*):\\s*(.*)-->", Qt::CaseSensitive, QRegExp::RegExp2);
    noteRx.setMinimal(true);
    pos = 0;

    while ((pos = noteRx.indexIn(m_contents, pos)) != -1) {
        key = noteRx.cap(1).trimmed();
        if (key[0] == '(' && key[key.length() -1] == ')')
        {
            noteKeyList = key.mid(1,key.length()-2).split(",");
            noteValue = noteRx.cap(2).simplified();
            for (int i = 0; i < noteKeyList.length(); i++)
            {
                translatable->setNote(noteKeyList[i], noteValue);
            }
        }
        pos += noteRx.matchedLength();
    }
}

void DTDFileType::writeFile(QString fileName, QString locale, Translatable *translatable)
{
    QFile file(fileName);
    file.open(QFile::WriteOnly | QFile::Truncate);
    QTextStream textStream(&file);
    QString key, value;
    QRegExp entityRx("<!ENTITY (.*)\\s*\"(.*)\">", Qt::CaseSensitive, QRegExp::RegExp2);
    entityRx.setMinimal(true);
    int pos = 0, lastpos = 0;

    while ((pos = entityRx.indexIn(m_contents, pos)) != -1) {
        
        key = entityRx.cap(1).trimmed();
        textStream << m_contents.mid(lastpos, pos - lastpos);
        textStream << "<!ENTITY " + key + " \"" + translatable->findString(key, locale) + "\">";
        pos += entityRx.matchedLength();
        lastpos = pos;
    }
}