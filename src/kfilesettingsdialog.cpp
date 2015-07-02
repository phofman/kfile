#include <QtGui/QApplication>
#include <QtGui/QPushButton>
#include <QtGui/QWidget>
#include <QtGui/QListWidget>
#include <QtGui/QMessageBox>
#include <QtGui/QAction>
#include <QtGui/QToolBar>
#include <QtGui/QVBoxLayout>
#include <QtCore/QFileInfo>
#include <QtGui/QTabWidget> 
#include <sys/platform.h>
#include <bps/event.h> 
#include <bps/navigator.h> 
#include <QtGui/QStatusBar> 
#include <QtGui/QInputDialog>
#include <QtGui/QProgressDialog>
#include <QtCore/QDir>

#include "mainwindow.h" 
#include "kfilesettings.h" 
#include "kfilesettingsdialog.h" 
#include "kfiledialogs.h" 


/*=========================================================================
  Constructor
=========================================================================*/
KFileSettingsDialog::KFileSettingsDialog(QWidget *parent, 
    KFileSettings *settings)
    : QDialog (parent)
  {
  this->settings = settings;
  mainLayout = new QVBoxLayout;

  buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok
      | QDialogButtonBox::Cancel);

  connect(buttonBox, SIGNAL(accepted()), this, SLOT(preAccept()));
  connect(buttonBox, SIGNAL(rejected()), this, SLOT(reject())); 

  skinGroupBox = new QGroupBox (tr("Appearance"));
  darkSkinRadio = new QRadioButton (tr("Dark"));
  lightSkinRadio = new QRadioButton (tr("Light"));
  darkSkinRadio->setChecked (true);
  skinLayout = new QVBoxLayout;
  skinLayout->addWidget (darkSkinRadio);
  skinLayout->addWidget (lightSkinRadio);
  skinGroupBox->setLayout (skinLayout);

  if (settings->getSkin() == KF_SKIN_LIGHT)
    lightSkinRadio->setChecked(true);
  else
    darkSkinRadio->setChecked(true);

  confirmGroupBox = new QGroupBox (tr("Confirmation"));
  confirmQuitCheck = new QCheckBox ("Quit");
  confirmDeleteCheck = new QCheckBox ("Delete");
  confirmMoveCheck = new QCheckBox ("Move");
  confirmLayout = new QVBoxLayout;
  confirmLayout->addWidget (confirmQuitCheck);
  confirmLayout->addWidget (confirmDeleteCheck);
  confirmLayout->addWidget (confirmMoveCheck);
  confirmGroupBox->setLayout (confirmLayout);

  browserGroupBox = new QGroupBox (tr("Browser"));
  jpegThumbnailsCheck = new QCheckBox ("JPEG thumbnails");
  browserLayout = new QVBoxLayout;
  browserLayout->addWidget (jpegThumbnailsCheck);
  browserGroupBox->setLayout (browserLayout);

  int flags = settings->getFlags();

  if (flags & KF_CONFIRM_DELETE)
    confirmDeleteCheck->setChecked (true);
  else
    confirmDeleteCheck->setChecked (false);

  if (flags & KF_CONFIRM_QUIT)
    confirmQuitCheck->setChecked (true);
  else
    confirmQuitCheck->setChecked (false);

  if (flags & KF_CONFIRM_MOVE)
    confirmMoveCheck->setChecked (true);
  else
    confirmMoveCheck->setChecked (false);

  if (flags & KF_JPEG_THUMBNAILS)
    jpegThumbnailsCheck->setChecked (true);
  else
    jpegThumbnailsCheck->setChecked (false);

  layout1 = new QHBoxLayout;
  layout1->addWidget (skinGroupBox);
  layout1->addWidget (confirmGroupBox);
  layout1->addWidget (browserGroupBox);

  mainLayout->addLayout (layout1);
  mainLayout->addWidget (buttonBox);
  setLayout (mainLayout);
  }

/*=========================================================================
  Destructor
=========================================================================*/
KFileSettingsDialog::~KFileSettingsDialog(void)
  {
  delete buttonBox;
  delete layout1;
  delete mainLayout;
  }

/*=========================================================================
  preAccept
=========================================================================*/
void KFileSettingsDialog::preAccept (void)
  {
  if (darkSkinRadio->isChecked())
    settings->setSkin (KF_SKIN_DARK);
  else
    settings->setSkin (KF_SKIN_LIGHT);

  int flags = 0;
  if (confirmQuitCheck->isChecked()) flags |= KF_CONFIRM_QUIT;
  if (confirmDeleteCheck->isChecked()) flags |= KF_CONFIRM_DELETE;
  if (confirmMoveCheck->isChecked()) flags |= KF_CONFIRM_MOVE;
  if (jpegThumbnailsCheck->isChecked()) flags |= KF_JPEG_THUMBNAILS;
  settings->setFlags (flags);

  done (Accepted);
  }



