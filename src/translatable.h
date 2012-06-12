#ifndef TRANSLATABLE_H
#define TRANSLATABLE_H

#include <QtCore>

typedef qint64 EntryIndex;
typedef QPair<QString, QString> StringHashKey;

class FileType;

class Translatable : public QObject
{
public:
    Translatable(FileType *fileType, QObject *parent = 0);
    ~Translatable();

    void readFile(QString inputFile);
    void writeFile(QString outputFile, QString locale);

    void addEntry(QString uik, EntryIndex entryNumber, QString note, QString locale, QString string);

    //TODO: There may be multiple notes for the same UIK
    void setNote(QString uik, QString note);

    QString findUik(EntryIndex entryNumber);
    EntryIndex findEntryIndex(QString uik);

    QString findNote(QString uik);
    QString findNote(EntryIndex entryNumber);
    QString findString(QString uik, QString locale);
    QString findString(EntryIndex entryNumber, QString locale);

    int entryCount();
private:
    QHash<QPair<QString, QString>, QString> *m_stringTable;
    QHash<QString, QString> *m_noteTable;
    QHash<QString, EntryIndex> *m_entryIndexTable;
    QHash<EntryIndex, QString> *m_uikTable;

    FileType *m_fileType;
};

inline uint qHash(StringHashKey &hashKey)
{
    return qHash(hashKey.first + hashKey.second);
}

#endif //TRANSLATABLE_H