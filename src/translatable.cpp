#include "translatable.h"
#include "filetype.h"

Translatable::Translatable(FileType *fileType, QObject *parent)
    : QObject(parent),
    m_fileType(fileType)
{
    m_stringTable = new QMultiHash<StringHashKey, QString>;
    m_noteTable = new QHash<QString, QString>;
    m_entryIndexTable = new QHash<QString, EntryIndex>;
    m_uikTable = new QHash<EntryIndex, QString>;
}

Translatable::~Translatable()
{
}

void Translatable::readFile(QString inputFile)
{
    Q_ASSERT(m_fileType);
    m_fileType->readFile(inputFile, this);
}

void Translatable::writeFile(QString outputFile, QString locale)
{
    Q_ASSERT(m_fileType);
    m_fileType->writeFile(outputFile, locale, this);
}

void Translatable::addEntry(QString uik, EntryIndex entryNumber, QString note, QString locale, QString string)
{
    if (m_entryIndexTable->contains(uik))
    {
        Q_ASSERT(m_stringTable);
        m_stringTable->insert(QPair<QString, QString>(uik, locale), string);
    }
    else
    {
        Q_ASSERT(m_stringTable);
        Q_ASSERT(m_entryIndexTable);
        Q_ASSERT(m_noteTable);
        Q_ASSERT(m_uikTable);
        m_stringTable->insert(QPair<QString, QString>(uik, locale), string);
        m_noteTable->insert(uik, note);
        m_entryIndexTable->insert(uik, entryNumber);
        m_uikTable->insert(entryNumber, uik);
    }
}

void Translatable::setNote(QString uik, QString note)
{
    Q_ASSERT(m_entryIndexTable);
    if (m_entryIndexTable->contains(uik))
    {
        Q_ASSERT(m_noteTable);
        m_noteTable->insert(uik, note);
    }
}

QString Translatable::findUik(EntryIndex entryNumber)
{
    Q_ASSERT(m_uikTable);
    return m_uikTable->value(entryNumber);
}

EntryIndex Translatable::findEntryIndex(QString uik)
{
    Q_ASSERT(m_entryIndexTable);
    return m_entryIndexTable->value(uik);
}

QString Translatable::findNote(QString uik)
{
    Q_ASSERT(m_noteTable);
    return m_noteTable->value(uik);
}

QString Translatable::findNote(EntryIndex entryNumber)
{
    QString uik = findUik(entryNumber);
    if (uik == QString())
        return QString();
    Q_ASSERT(m_noteTable);
    return m_noteTable->value(uik);
}

QString Translatable::findString(QString uik, QString locale)
{
    Q_ASSERT(m_stringTable);
    return m_stringTable->value(QPair<QString, QString>(uik, locale));
}

QString Translatable::findString(EntryIndex entryNumber, QString locale)
{
    QString uik = findUik(entryNumber);
    if (uik == QString())
        return QString();
    Q_ASSERT(m_stringTable);
    return m_stringTable->value(QPair<QString, QString>(uik, locale));
}

int Translatable::entryCount()
{
    Q_ASSERT(m_uikTable);
    return m_uikTable->size();
}