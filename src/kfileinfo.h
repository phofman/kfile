#pragma once

#include <QtCore/QString>
#include <QtCore/QFileInfo>

class KFileInfo
{
public:
    static const int Full;
    static const int Brief;

protected:
    KFileInfo(const QString &path);

public:
    static KFileInfo *getInstance(const QString &path, int flags);
    virtual QString statusLineSummary(void) const;
    static QString formatSize(qint64 size);
    static QString formatModified(const QDateTime &modified);
    static QString formatPermissions(QFile::Permissions permissions);

protected:
    QString path;
    QFileInfo info;
};

