#pragma once

#include <QObject>
#include <QWidget>
#include <QDialog>
#include <QDialogButtonBox>
#include <QGroupBox>
#include <QRadioButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QCheckBox>
#include "kfilesettings.h"

class KFileSettingsDialog : public QDialog
 {
 Q_OBJECT

 public:
 
   KFileSettingsDialog (QWidget *parent, KFileSettings *settings);
   ~KFileSettingsDialog (void);

  protected slots:

  void preAccept (void);

  protected:
  
   QDialogButtonBox *buttonBox;
   QGroupBox *skinGroupBox;
   QGroupBox *confirmGroupBox;
   QGroupBox *browserGroupBox;
   QRadioButton *darkSkinRadio;
   QRadioButton *lightSkinRadio;
   QVBoxLayout *skinLayout;
   QVBoxLayout *confirmLayout;
   QVBoxLayout *browserLayout;
   QVBoxLayout *mainLayout;
   QHBoxLayout *layout1;
   KFileSettings *settings;
   QCheckBox *confirmDeleteCheck;
   QCheckBox *confirmQuitCheck;
   QCheckBox *confirmMoveCheck;
   QCheckBox *jpegThumbnailsCheck;
 };

