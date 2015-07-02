#include <stdlib.h>
#include <QtCore/QSettings>
#include "kfilesettings.h"

KFileSettings *instance = 0;

/*=========================================================================
  constructor 
=========================================================================*/
KFileSettings::KFileSettings(void)
{
    skin = KF_SKIN_DARK;
    flags = KF_CONFIRM_DELETE | KF_CONFIRM_QUIT | KF_CONFIRM_MOVE
        | KF_JPEG_THUMBNAILS;
}

/*=========================================================================
  getInstance
=========================================================================*/
KFileSettings *KFileSettings::getGlobalInstance(void)
{
    if (instance == 0)
        instance = new KFileSettings;
    return instance;
}

/*=========================================================================
  set 
=========================================================================*/
void KFileSettings::set(const KFileSettings *other)
{
    skin = other->skin;
    flags = other->flags;
}

/*=========================================================================
  getIniFile 
=========================================================================*/
QString KFileSettings::getIniFile(void) const
{
    return QString(getenv("HOME")) + "/" + "kfile.txt";
}

/*=========================================================================
  load 
=========================================================================*/
void KFileSettings::load(void)
{
    QString iniFile = getIniFile();
    QSettings qs(iniFile, QSettings::IniFormat);
    skin = (KFSkin)qs.value("skin").toInt();
    flags = qs.value("flags").toInt();
}

/*=========================================================================
  load 
=========================================================================*/
void KFileSettings::save(void)
{
    QString iniFile = getIniFile();
    QSettings qs(iniFile, QSettings::IniFormat);
    qs.setValue("skin", skin);
    qs.setValue("flags", flags);
}
