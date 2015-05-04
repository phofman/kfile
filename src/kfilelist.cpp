#include <unistd.h> 
#include <QApplication>
#include <QPushButton>
#include <QWidget>
#include <QListWidget>
#include <QDir>
#include <QStringList>
#include <QMessageBox>
#include <QVBoxLayout>
#include <QAction>
#include <QToolBar>
#include <QAbstractItemView>
#include <QInputDialog>
#include <QProgressDialog>
#include <QToolButton>
#include <QMenu>

#include "kfilelist.h"
#include "fileclipboard.h"
#include "kfilewidget.h"
#include "kfiledialogs.h"

/*=========================================================================
  Constructor
=========================================================================*/
KFileList::KFileList(const QString &caption, const QString &path, 
        QWidget *parent)
    : KFileWidget (path, parent)
  {
  QLayout *layout = new QVBoxLayout;

  toolbar = new QToolBar ();
  toolbar->setToolButtonStyle (Qt::ToolButtonTextUnderIcon);


  QAction *exitAction = new QAction (*exitIcon, "E&xit", toolbar);
  QObject::connect(exitAction, SIGNAL(triggered(bool)), 
      this, SLOT(handleExitAction()));

  QAction *openAction = new QAction (*openIcon, "&Open", toolbar);
  QObject::connect(openAction, SIGNAL(triggered(bool)), 
      this, SLOT(handleOpenAction()));

  QAction *deleteAction = new QAction (*deleteIcon, "&Delete", 
      toolbar);
  QObject::connect(deleteAction, SIGNAL(triggered(bool)), 
      this, SLOT(handleDeleteAction()));

  QAction *cutAction = new QAction (*cutIcon, "&Cut", 
      toolbar);
  QObject::connect(cutAction, SIGNAL(triggered(bool)), 
      this, SLOT(handleCutAction()));

  QAction *copyAction = new QAction (*copyIcon, "&Copy", 
      toolbar);
  QObject::connect(copyAction, SIGNAL(triggered(bool)), 
      this, SLOT(handleCopyAction()));

  QAction *settingsAction = new QAction (*settingsIcon, "Settings", 
      toolbar);
  QObject::connect(settingsAction, SIGNAL(triggered(bool)), 
      this, SLOT(handleSettingsAction()));

  QAction *newBrowserAction = new QAction (*newBrowserIcon, "New browser", 
      toolbar);
  QObject::connect(newBrowserAction, SIGNAL(triggered(bool)), 
      this, SLOT(handleNewBrowserAction()));

  QAction *manualAction = new QAction (*manualIcon, "Manual", 
      toolbar);
  QObject::connect(manualAction, SIGNAL(triggered(bool)), 
      this, SLOT(handleManualAction()));

  QAction *aboutAction = new QAction (*aboutIcon, "About", 
      toolbar);
  QObject::connect(aboutAction, SIGNAL(triggered(bool)), 
      this, SLOT(handleAboutAction()));

  QAction *selectAllAction = new QAction (*selectAllIcon, "Select all", 
      toolbar);
  QObject::connect(selectAllAction, SIGNAL(triggered(bool)), 
      this, SLOT(handleSelectAllAction()));

  QAction *selectNoneAction = new QAction (*selectNoneIcon, "Select none", 
      toolbar);
  QObject::connect(selectNoneAction, SIGNAL(triggered(bool)), 
      this, SLOT(handleSelectNoneAction()));

  editMenu = new QMenu ();
  QToolButton *editButton = new QToolButton();
  editMenu->addAction (deleteAction);
  editMenu->addAction (cutAction);
  editMenu->addAction (copyAction);
  editMenu->addSeparator();
  editMenu->addAction (selectAllAction);
  editMenu->addAction (selectNoneAction);
  editButton->setMenu (editMenu);
  editButton->setIcon (*copyIcon);
  editButton->setPopupMode (QToolButton::InstantPopup);
  editButton->setText ("Edit");
  editButton->setToolButtonStyle (Qt::ToolButtonTextUnderIcon);

  newMenu = new QMenu ();
  QToolButton *newButton = new QToolButton();
  newMenu->addAction (newBrowserAction);
  newButton->setMenu (newMenu);
  newButton->setIcon (*newBrowserIcon);
  newButton->setPopupMode (QToolButton::InstantPopup);
  newButton->setText ("New");
  newButton->setToolButtonStyle (Qt::ToolButtonTextUnderIcon);

  helpMenu = new QMenu ();
  QToolButton *helpButton = new QToolButton();
  helpMenu->addAction (manualAction);
  helpMenu->addAction (aboutAction);
  helpButton->setMenu (helpMenu);
  helpButton->setIcon (*helpIcon);
  helpButton->setPopupMode (QToolButton::InstantPopup);
  helpButton->setText ("Help");
  helpButton->setToolButtonStyle (Qt::ToolButtonTextUnderIcon);

  toolbar->addAction (exitAction);
  toolbar->addAction (openAction);
  toolbar->addWidget(newButton);
  toolbar->addWidget(editButton);
  toolbar->addAction (settingsAction);
  toolbar->addWidget (helpButton);
  
  captionDisplay = new QLabel (caption);
  captionDisplay->setObjectName ("captionDisplay");

  layout->addWidget (toolbar);
  layout->addWidget (captionDisplay);
  layout->addWidget (list);

  setLayout (layout);

  pasteByNameOnly = true;
  }

/*=========================================================================
  Destructor
=========================================================================*/
KFileList::~KFileList()
  {
  if (captionDisplay) delete captionDisplay;
  if (toolbar) delete toolbar;
  if (newMenu) delete newMenu;
  if (editMenu) delete editMenu;
  if (helpMenu) delete helpMenu;
  }

/*=========================================================================
  setNames
=========================================================================*/
void KFileList::setNames (const QStringList &names)
  {
  int l = names.count();
  for (int i = 0; i < l; i++)
    {
    QListWidgetItem *item = new QListWidgetItem(names[i], list);
    item->setIcon (getIconForFile (path + "/" + names[i]));
    QSize size (200, 50);
    item->setSizeHint (size);
    }
  }

/*=========================================================================
  slot exitAction 
=========================================================================*/
void KFileList::handleExitAction (void)
  {
  emit closeRequested (this);
  }

/*=========================================================================
  addName 
=========================================================================*/
void KFileList::addName (const QString &name)
  {
  QListWidgetItem *item = new QListWidgetItem(name, list);
  item->setIcon (getIconForFile (path + "/" + name));
  QSize size (200, 50);
  item->setSizeHint (size);
  }

/*=========================================================================
  refresh 
=========================================================================*/
void KFileList::refresh (void)
  {
  // Can't refresh
  }

/*=========================================================================
  openSingleDir
=========================================================================*/
void KFileList::openSingleDir (const QString &dirName)
  {
  // TODO
  }

/*=========================================================================
  slot newBrowserAction 
=========================================================================*/
void KFileList::handleNewBrowserAction (void)
  {
  QString empty;
  emit newBrowserRequested (&empty);
  }


