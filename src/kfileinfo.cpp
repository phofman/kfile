#include <QtGui/QWidget>
#include <QtCore/QFileInfo>
#include <QtCore/QDateTime>
#include "kfileinfo.h"

const int KFileInfo::Brief = 0x00000000;
const int KFileInfo::Full  = 0x00000001;

/*=========================================================================
  constructor 
=========================================================================*/
KFileInfo::KFileInfo(const QString &path)
    : info(path)
{
    this->path = path;
}

/*=========================================================================
  getInstance 
=========================================================================*/
KFileInfo *KFileInfo::getInstance(const QString &path, int flags)
{
    return new KFileInfo(path);
}

/*=========================================================================
  formatModified
=========================================================================*/
QString KFileInfo::formatModified(const QDateTime &modified)
{
    return modified.toString(Qt::SystemLocaleShortDate);
}

/*=========================================================================
  formatPermissions
=========================================================================*/
QString KFileInfo::formatPermissions(QFile::Permissions permissions)
{
    QString s = "";
    if (permissions & QFile::ReadUser)
        s += "R";
    else
        s += "-";
    if (permissions & QFile::WriteUser)
        s += "W";
    else
        s += "-";
    if (permissions & QFile::ExeUser)
        s += "X";
    else
        s += "-";
    return s;
}

/*=========================================================================
  formatSize 
=========================================================================*/
QString KFileInfo::formatSize(qint64 size)
{
    if (size < 1024)
        return QString::number(size) + " " + QWidget::tr("bytes");
    else if (size < 1000000)
        return QString::number(size / 1024) + " " + QWidget::tr("kB");
    else if (size < 1000000000)
        return QString::number(size / 1000000) + " " + QWidget::tr("MB");
    else
        return QString::number(size / 1000000000) + " " + QWidget::tr("GB");
}

/*=========================================================================
  statusLineSummary 
=========================================================================*/
QString KFileInfo::statusLineSummary(void) const
{
    QString s;
    if (info.isDir())
    {
        s = info.fileName() + ": " + QWidget::tr("modified") + " "
            + formatModified(info.lastModified())
            + ", " + formatPermissions(info.permissions());
    }
    else
    {
        s = info.fileName() + ": " + formatSize(info.size()) + ", "
            + QWidget::tr("modified") + " " + formatModified(info.lastModified())
            + ", " + formatPermissions(info.permissions());
    }
    if (info.isSymLink())
        s += ", link";
    return s;
}


