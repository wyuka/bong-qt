#include <propertiesfiletype.h>
#include <QtCore>

void PropertiesFileType::readFile(QString fileName, Translatable *translatable)
{
    QString line, note;
    QStringList keyList;
    QFile file(fileName);
    file.open(QFile::ReadOnly);
    QTextStream textStream(&file);
    QList< QPair<QString, QString> > noteList;
    const QString localizationStart = "# LOCALIZATION NOTE";
    bool insideNote = false;
    int entryCount = 0;

    while (1)
    {
        line = textStream.readLine();
        if (line.isNull())
            break;
        m_lineList << line;
        line = line.trimmed();

        //if line is a comment
        if (line.startsWith('#'))
        {
            //if line starts a new note
            if (line.startsWith(localizationStart))
            {
                //if another note just ended
                if (insideNote == true)
                {
                    foreach (QString key, keyList)
                    {
                        noteList << QPair<QString, QString>(key, note);
                    }
                    note = QString();
                }
                //may start a note here
                int start = line.indexOf("(");
                if (start == -1)
                    continue;
                int end = line.indexOf(")", start);
                if (end == -1)
                    continue;
                insideNote = true;
                note = line.mid(line.indexOf(":", end) + 1, -1).trimmed();
                QString commaSep = line.mid(start + 1, end - start - 1);
                keyList = commaSep.split(",");
            }
            else
            {
                if (insideNote)
                {
                    note += "\n" + line.mid(1,-1).trimmed();
                }
            }
        }
        else
        {
            //end note
            if (insideNote)
            {
                foreach (QString key, keyList)
                {
                    noteList << QPair<QString, QString>(key, note);
                }
                note = QString();
                insideNote = false;
            }
            int equalPos;
            if ((equalPos = line.indexOf("=")) == -1)
                continue;
            QString key = line.mid(0, equalPos).trimmed();
            QString value = line.mid(equalPos + 1, -1).trimmed();
            translatable->addEntry(key, entryCount++, QString(), "en", value);
        }
    }
    QPair <QString, QString> pair;
    foreach (pair, noteList)
    {
        translatable->setNote(pair.first, pair.second);
    }
}

void PropertiesFileType::writeFile(QString fileName, QString locale, Translatable *translatable)
{
    QFile file(fileName);
    file.open(QFile::WriteOnly | QFile::Truncate);
    QTextStream textStream(&file);
    QString key, value, line;
    int equalPos;
    foreach (line, m_lineList)
    {
        if (line.trimmed().startsWith("#") || ((equalPos = line.indexOf("=")) == -1))
            textStream << line << endl;
        else
        {
            key = line.mid(0, equalPos).trimmed();
            value = translatable->findString(key, locale);
            textStream << key << "=" << value << endl;
        }
    }
}