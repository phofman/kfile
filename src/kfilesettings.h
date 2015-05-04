#pragma once

#include <QString>

typedef enum
  {
  KF_SKIN_DARK=0,
  KF_SKIN_LIGHT
  } KFSkin;


#define KF_CONFIRM_DELETE    0x00000001
#define KF_CONFIRM_QUIT      0x00000002
#define KF_CONFIRM_MOVE      0x00000004
#define KF_JPEG_THUMBNAILS   0x00000100

class KFileSettings
 {

 public:

   KFileSettings (void);
   static KFileSettings *getGlobalInstance (void);
   void set (const KFileSettings *other);
   void save (void);
   void load (void);
   KFSkin getSkin (void) const { return skin; }
   void setSkin (KFSkin f) { skin = f; }
   int getFlags (void) const { return flags; }
   void setFlags (int f) { flags = f; }

  protected:

    QString getIniFile (void) const;
    KFSkin skin;
    int flags;
 };


