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

#include "kfilewidget.h"
#include "kfilebrowser.h"
#include "fileclipboard.h"
#include "kfiledialogs.h"

/*=========================================================================
  Constructor
=========================================================================*/
KFileBrowser::KFileBrowser(QWidget *parent)
    : KFileWidget (path, parent)
  {
  QLayout *layout = new QVBoxLayout;

  homeDir = getHomeDir(); 
  
  toolbar = new QToolBar ();
  toolbar->setToolButtonStyle (Qt::ToolButtonTextUnderIcon);

  QAction *exitAction = new QAction (*exitIcon, "Exit", toolbar);
  QObject::connect(exitAction, SIGNAL(triggered(bool)), 
      this, SLOT(handleExitAction()));

  QAction *openAction = new QAction (*openIcon, "Open", toolbar);
  QObject::connect(openAction, SIGNAL(triggered(bool)), 
      this, SLOT(handleOpenAction()));

  QAction *upAction = new QAction (*upIcon, "Up", toolbar);
  QObject::connect(upAction, SIGNAL(triggered(bool)), 
      this, SLOT(handleUpAction()));

  QAction *homeAction = new QAction (*homeIcon, "Home", toolbar);
  QObject::connect(homeAction, SIGNAL(triggered(bool)), 
      this, SLOT(handleHomeAction()));

  QAction *viewAction = new QAction (*viewIcon, "View", toolbar);
  QObject::connect(viewAction, SIGNAL(triggered(bool)), 
      this, SLOT(handleViewAction()));

  QAction *newBrowserAction = new QAction (*newBrowserIcon, "New browser", 
      toolbar);
  QObject::connect(newBrowserAction, SIGNAL(triggered(bool)), 
      this, SLOT(handleNewBrowserAction()));

  QAction *newFileAction = new QAction (*newFileIcon, "New file", 
      toolbar);
  QObject::connect(newFileAction, SIGNAL(triggered(bool)), 
      this, SLOT(handleNewFileAction()));

  QAction *newDirAction = new QAction (*newDirIcon, "New folder", 
      toolbar);
  QObject::connect(newDirAction, SIGNAL(triggered(bool)), 
      this, SLOT(handleNewDirAction()));

  QAction *deleteAction = new QAction (*deleteIcon, "Delete", 
      toolbar);
  QObject::connect(deleteAction, SIGNAL(triggered(bool)), 
      this, SLOT(handleDeleteAction()));

  QAction *cutAction = new QAction (*cutIcon, "Cut", 
      toolbar);
  QObject::connect(cutAction, SIGNAL(triggered(bool)), 
      this, SLOT(handleCutAction()));

  QAction *copyAction = new QAction (*copyIcon, "Copy", 
      toolbar);
  QObject::connect(copyAction, SIGNAL(triggered(bool)), 
      this, SLOT(handleCopyAction()));

  QAction *pasteAction = new QAction (*pasteIcon, "Paste", 
      toolbar);
  QObject::connect(pasteAction, SIGNAL(triggered(bool)), 
      this, SLOT(handlePasteAction()));

  QAction *refreshAction = new QAction (*refreshIcon, "Refresh", 
      toolbar);
  QObject::connect(refreshAction, SIGNAL(triggered(bool)), 
      this, SLOT(handleRefreshAction()));

  QAction *searchAction = new QAction (*searchIcon, "Search", 
      toolbar);
  QObject::connect(searchAction, SIGNAL(triggered(bool)), 
      this, SLOT(handleSearchAction()));

  QAction *settingsAction = new QAction (*settingsIcon, "Settings", 
      toolbar);
  QObject::connect(settingsAction, SIGNAL(triggered(bool)), 
      this, SLOT(handleSettingsAction()));

  QAction *manualAction = new QAction (*manualIcon, "Manual", 
      toolbar);
  QObject::connect(manualAction, SIGNAL(triggered(bool)), 
      this, SLOT(handleManualAction()));

  QAction *aboutAction = new QAction (*aboutIcon, "About", 
      toolbar);
  QObject::connect(aboutAction, SIGNAL(triggered(bool)), 
      this, SLOT(handleAboutAction()));

  QAction *renameAction = new QAction (*renameIcon, "Rename", 
      toolbar);
  QObject::connect(renameAction, SIGNAL(triggered(bool)), 
      this, SLOT(handleRenameAction()));

  QAction *selectAllAction = new QAction (*selectAllIcon, "Select all", 
      toolbar);
  QObject::connect(selectAllAction, SIGNAL(triggered(bool)), 
      this, SLOT(handleSelectAllAction()));

  QAction *selectNoneAction = new QAction (*selectNoneIcon, "Select none", 
      toolbar);
  QObject::connect(selectNoneAction, SIGNAL(triggered(bool)), 
      this, SLOT(handleSelectNoneAction()));

  newMenu = new QMenu ();
  QToolButton *newButton = new QToolButton();
  newMenu->addAction (newBrowserAction);
  newMenu->addAction (newDirAction);
  newMenu->addAction (newFileAction);
  newButton->setMenu (newMenu);
  newButton->setIcon (*newBrowserIcon);
  newButton->setPopupMode (QToolButton::InstantPopup);
  newButton->setText ("New");
  newButton->setToolButtonStyle (Qt::ToolButtonTextUnderIcon);

  editMenu = new QMenu ();
  QToolButton *editButton = new QToolButton();
  editMenu->addAction (deleteAction);
  editMenu->addAction (cutAction);
  editMenu->addAction (copyAction);
  editMenu->addAction (pasteAction);
  editMenu->addAction (renameAction);
  editMenu->addSeparator();
  editMenu->addAction (selectAllAction);
  editMenu->addAction (selectNoneAction);
  editButton->setMenu (editMenu);
  editButton->setIcon (*copyIcon);
  editButton->setPopupMode (QToolButton::InstantPopup);
  editButton->setText ("Edit");
  editButton->setToolButtonStyle (Qt::ToolButtonTextUnderIcon);

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
  toolbar->addAction (refreshAction);
  toolbar->addAction (openAction);
  toolbar->addAction (upAction);
  toolbar->addAction (homeAction);
  toolbar->addAction (viewAction);
  toolbar->addAction (searchAction);
  toolbar->addWidget(newButton);
  toolbar->addWidget(editButton);
  toolbar->addAction (settingsAction);
  toolbar->addWidget (helpButton);
  
  pathDisplay = new QLabel ();
  pathDisplay->setObjectName ("pathDisplay");
  pathDisplay->setTextFormat (Qt::PlainText);

  layout->addWidget (toolbar);
  layout->addWidget (pathDisplay);
  layout->addWidget (list);

  setLayout (layout);

  pasteByNameOnly = false;
  }

/*=========================================================================
  getHomeDir 
=========================================================================*/
QString KFileBrowser::getHomeDir (void)
  {
  return "/accounts/1000/shared";
  }

/*=========================================================================
  Destructor
=========================================================================*/
KFileBrowser::~KFileBrowser()
  {
  if (pathDisplay) delete pathDisplay;
  if (toolbar) delete toolbar;
  if (newMenu) delete newMenu;
  if (editMenu) delete editMenu;
  if (helpMenu) delete helpMenu;
  }

/*=========================================================================
  refresh 
=========================================================================*/
void KFileBrowser::refresh (void)
  {
  setPath (this->path);
  }

/*=========================================================================
  setPath 
=========================================================================*/
void KFileBrowser::setPath (const QString &_path)
  {
  QString path;
  if (_path != "")
    path = _path;
  else
    path = homeDir;

  QDir dir(path, "*", QDir::DirsFirst);
  if (dir.isReadable())
    {
    emit statusUpdate (tr("Scanning folder..."));
    list->clear();
    QStringList entries = dir.entryList();
    QStringList::ConstIterator it = entries.constBegin();
    int count = 0;
    while (it != entries.constEnd()) 
      {
      if (*it != "." && *it != "..")
        {
        QListWidgetItem *item = new QListWidgetItem(*it, list);
        item->setIcon (getIconForFile (path + "/" + *it));
        //QSize size (200, 50);
        //item->setSizeHint (size);
        count++;
        }
      ++it;
      }
    this->path = dir.canonicalPath();
    pathDisplay->setText (this->path);
    QString title;
    if (this->path == "/")
      title = tr("Files: ") + "/"; 
    else
      title = tr("Files: ") + QFileInfo(this->path).fileName();
    emit tabTitleChanged ((QWidget *)this, &title);
    setViewMode (viewMode);
    if (count == 0)
      emit statusUpdate (tr("Folder empty"));
    else if (count == 1)
      emit statusUpdate (QString::number (count) + " " + tr("item") 
        + " " + tr("in folder"));
    else
      emit statusUpdate (QString::number (count) + " " + tr("items") 
        + " " + tr("in folder"));
    }
   else
    {
    QMessageBox msgBox;
    msgBox.setIcon(QMessageBox::Critical);
    msgBox.setText("Can't read directory");
    msgBox.exec();
    }
  }

/*=========================================================================
  getCurrentItem 
=========================================================================*/
QString KFileBrowser::getCurrentItem (void) const 
  {
  QListWidgetItem *item = list->currentItem();
  if (item)
    {
    QString newPath = path + "/" + list->currentItem()->text();
    return newPath;
    }
  else
    return ("");
  }

/*=========================================================================
  up 
=========================================================================*/
void KFileBrowser::up (void) 
  {
  QString newPath = path + "/..";
  setPath (newPath);
  }

/*=========================================================================
  slot upAction 
=========================================================================*/
void KFileBrowser::handleUpAction (void)
  {
  up();
  }

/*=========================================================================
  slot homeAction 
=========================================================================*/
void KFileBrowser::handleHomeAction (void)
  {
  setPath (homeDir);
  }

/*=========================================================================
  slot viewAction 
=========================================================================*/
void KFileBrowser::handleViewAction (void)
  {
  toggleViewMode();
  }

/*=========================================================================
  slot exitAction 
=========================================================================*/
void KFileBrowser::handleExitAction (void)
  {
  emit closeRequested (this);
  }

/*=========================================================================
  slot newFileAction 
=========================================================================*/
void KFileBrowser::handleNewFileAction (void)
  {
  bool ok = false;
  QString name = QInputDialog::getText (this, tr("Filename"),
    tr("Enter filename:"), QLineEdit::Normal, "", &ok);
  if (ok && !name.isEmpty())
    {
    bool doIt = false;
    QString pathName = path + "/" + name;
    QFile file (pathName);
    if (file.exists())
      {
      error ("The file already exists: " + pathName); 
      doIt = false;
      }
    else
      doIt = true;
    if (doIt)
      {
      if (file.open (QIODevice::WriteOnly))
        {
        file.close();
        emit dirContentsChanged();
        emit statusUpdate (tr("Created file") + " " +
          pathName);
        }
      else
        error ("Can't write file: " + pathName);
      }
    }
  }

/*=========================================================================
  slot newDirAction 
=========================================================================*/
void KFileBrowser::handleNewDirAction (void)
  {
  bool ok = false;
  QString name = QInputDialog::getText (this, tr("Folder name"),
    tr("Enter folder name:"), QLineEdit::Normal, "", &ok);
  if (ok && !name.isEmpty())
    {
    bool doIt = false;
    QString pathName = path + "/" + name;
    QDir dir (pathName);
    if (dir.exists())
      {
      error ("The folder already exists: " + pathName); 
      doIt = false;
      }
    else
      doIt = true;
    if (doIt)
      {
      if (dir.mkdir (pathName))
        {
        emit dirContentsChanged();
        emit statusUpdate (tr("Created folder") + " " +
          pathName);
        }
      else
        error ("Can't create directory: " + pathName);
      }
    }
  }

/*=========================================================================
  slot newBrowserAction 
=========================================================================*/
void KFileBrowser::handleNewBrowserAction (void)
  {
  QString empty;
  QString fileName = getCurrentItem();
  if (fileName != "")
    {
    if (QFileInfo(fileName).isDir())
      {
      emit newBrowserRequested (&fileName);
      }
    else
      emit newBrowserRequested (&empty);
    }
  else
    {
    emit newBrowserRequested (&empty);
    }
  }

/*=========================================================================
  copyFromClipboard 
=========================================================================*/
bool KFileBrowser::copyFromClipboard (const FileClipboard *fc)
  {
  bool ret = FALSE;
  const QStringList &names = fc->getNames();
  const QString &root = fc->getRoot();
  int l = names.count();
  int filesDone = 0;
  int dirsDone = 0;

  QProgressDialog progress (tr("Copying files..."), tr("Stop"), 
      0, l, this);
  progress.setWindowModality (Qt::WindowModal);
  progress.setMinimumDuration (0);
  progress.show();
  bool stop = false;
  QString errorMessage = "";
  for (int i = 0; i < l && !progress.wasCanceled() &&!stop; i++)
    {
    QString sourceName = root + "/" + names[i];

    QString targetName;
    if (fc->getPasteByNameOnly())
      {
      QFileInfo info (path + "/" + names[i]);
      QString shortName = info.fileName(); 
      targetName = path + "/" + shortName;
      }
    else
      targetName = path + "/" + names[i];

    errorMessage = "";

    if (sourceName == targetName)
      {
      errorMessage = tr ("Source and destination files are the same");
      }
    else
      {
      QFileInfo info (sourceName);
      if (info.isDir())
        {
        QDir dir;
        if (dir.mkpath (targetName))
          dirsDone++;
        else
          errorMessage = tr ("Can't create folder") + " " + targetName;
        }
      else
        {
        bool doCopy = false;
        QFile targetFile (targetName);
        QFile sourceFile (sourceName);
        if (targetFile.exists())
          {
          QMessageBox msgBox;
          msgBox.setText(tr("File exists"));
          msgBox.setInformativeText
            (errorMessage + ". " + 
              tr("Do you want to overwrite file") + " " + targetName + "?");
          msgBox.setStandardButtons(QMessageBox::Ok 
             | QMessageBox::Cancel);
          msgBox.setDefaultButton(QMessageBox::Cancel);
          int ret = msgBox.exec();
          if (ret == QMessageBox::Ok)
            doCopy = true;
          else
            doCopy = false;
          }
        else
          doCopy = true;
        if (doCopy)
          {
          targetFile.remove();
          if (sourceFile.copy(targetName))
            {
            filesDone++;
            }
          else
            {
            errorMessage = tr ("Can't copy file") + " " + sourceName + 
              " " + tr("to") + " " + targetName;
            }
          }
        }
      }

    if (errorMessage != "")
      {
      if (i < l - 1)
        {
        QMessageBox msgBox;
        msgBox.setText(tr("Error copying file"));
        msgBox.setInformativeText
          (errorMessage + ". " + 
             tr("Do you want to coninue with the next item?"));
        msgBox.setStandardButtons(QMessageBox::Ok 
            | QMessageBox::Cancel);
        msgBox.setDefaultButton(QMessageBox::Cancel);
        int ret = msgBox.exec();
        if (ret != QMessageBox::Ok) stop = true;
        }
      else
        error (errorMessage);
      }

    progress.setValue (i);
    }

  if (progress.wasCanceled()) message ("canceled");

  progress.setValue (l);
  ret = true;
  if (stop) ret = false;
  if (progress.wasCanceled()) ret = false;
  if (errorMessage != "") ret = false;

  emit dirContentsChanged();

  QString sm = tr("Copied");
  char ss[20];
  sprintf (ss, "%d", filesDone);
  sm += ss;
  sm += " " + (filesDone == 1 ? tr("file") : tr("files"));
  emit statusUpdate (sm);

  return ret;
  }

/*=========================================================================
  cutFromClipboard 
=========================================================================*/
bool KFileBrowser::cutFromClipboard (const FileClipboard *fc)
  {
  const QStringList &names = fc->getNames();
  QMessageBox msgBox;
  msgBox.setText(tr("Confirm move"));
  if (names.count() == 1)
    msgBox.setInformativeText
        (tr("Do you want to move this item?"));
 else
    {
    char ss[20];
    sprintf (ss, "%d", names.count());
    msgBox.setInformativeText
        ((QString)tr("Do you want to move these") + " " + ss + " " 
          + tr ("items") +  "?");
    }
  msgBox.setStandardButtons(QMessageBox::Ok 
      | QMessageBox::Cancel);
  msgBox.setDefaultButton(QMessageBox::Cancel);
  int r = msgBox.exec();
  if (r != QMessageBox::Ok) return false; 

  bool ret = FALSE;
  const QString &root = fc->getRoot();
  int l = names.count();
  int itemsDone = 0;

  QProgressDialog progress (tr("Moving files..."), tr("Stop"), 
      0, l, this);
  progress.setWindowModality (Qt::WindowModal);
  progress.setMinimumDuration (0);
  progress.show();
  bool stop = false;
  QString errorMessage = "";
  for (int i = 0; i < l && !progress.wasCanceled() &&!stop; i++)
    {
    QString sourceName = root + "/" + names[i];
    QString targetName;
    if (fc->getPasteByNameOnly())
      {
      QFileInfo info (path + "/" + names[i]);
      QString shortName = info.fileName(); 
      targetName = path + "/" + shortName;
      }
    else
      targetName = path + "/" + names[i];

    errorMessage = "";

    if (sourceName == targetName)
      {
      errorMessage = tr ("Source and destination files are the same");
      }
    else
      {
      QFileInfo info (sourceName);
      if (info.isDir())
        {
        QDir dir;
        if (dir.rename (sourceName, targetName))
          itemsDone++;
        else
          errorMessage = tr("Can't move directory");
        }
      else
        {
        QFile file;
        if (file.rename (sourceName, targetName))
          itemsDone++;
        else
          errorMessage = tr("Can't move file");
        }
      }

    if (errorMessage != "")
      {
      if (i < l - 1)
        {
        QMessageBox msgBox;
        msgBox.setText(tr("Error copying file"));
        msgBox.setInformativeText
          (errorMessage + ". " + 
             tr("Do you want to coninue with the next item?"));
        msgBox.setStandardButtons(QMessageBox::Ok 
            | QMessageBox::Cancel);
        msgBox.setDefaultButton(QMessageBox::Cancel);
        int ret = msgBox.exec();
        if (ret != QMessageBox::Ok) stop = true;
        }
      else
        error (errorMessage);
      }

    progress.setValue (i);
    }

  if (progress.wasCanceled()) message ("canceled");

  progress.setValue (l);
  ret = true;
  if (stop) ret = false;
  if (progress.wasCanceled()) ret = false;
  if (errorMessage != "") ret = false;

  emit dirContentsChanged();

  QString sm = tr("Moved");
  char ss[20];
  sprintf (ss, "%d", itemsDone);
  sm += ss;
  sm += " " + (itemsDone == 1 ? tr("items") : tr("items"));
  emit statusUpdate (sm);

  return ret;
  }

/*=========================================================================
  slot handlePasteAction 
=========================================================================*/
void KFileBrowser::handlePasteAction (void)
  {
  FileClipboard *fc = FileClipboard::getInstance();
  if (fc->getNames().count())
    {
    switch (fc->getOp())
      {
      case FILE_OP_COPY:
        if (copyFromClipboard (fc))
          fc->clear();
        break;
      case FILE_OP_CUT:
        if (cutFromClipboard (fc))
          fc->clear();
        break;
      default:; // Should never happen
      }
    } 
  else
    {
    message ("There is nothing on the clipboard.");
    }
  }

/*=========================================================================
  slot handleRefreshAction 
=========================================================================*/
void KFileBrowser::handleRefreshAction (void)
  {
  refresh();
  }

/*=========================================================================
  slot handleSearchAction 
=========================================================================*/
void KFileBrowser::handleSearchAction (void)
  {
  emit searchFromPath (path);
  }

/*=========================================================================
  openSingleDir
=========================================================================*/
void KFileBrowser::openSingleDir (const QString &dirName)
  {
  setPath (dirName);
  }

/*=========================================================================
  slot handleRenameAction 
=========================================================================*/
void KFileBrowser::handleRenameAction (void)
  {
  QStringList names = getSelectedItems ();
  if (names.count() != 1)
    {
    error (tr("Please select exactly one file or folder to rename"));
    }
  else
    { 
    QString sourcePath = path + "/" + names[0];
    QFileInfo sourceInfo (sourcePath);
    QDir sourceDir = sourceInfo.dir();
    QString sourceFilename = sourceInfo.fileName();
    bool ok = false;
    QString newName = QInputDialog::getText (this, tr("Rename"),
    tr("Enter new name for") + " " + sourceFilename, 
      QLineEdit::Normal, "", &ok);
    if (ok && !newName.isEmpty())
      {
      QString targetPath = sourceDir.path() + "/" + newName;
      bool ok = false;
      if (sourceInfo.isDir())
        {
        QDir d (sourcePath);
        ok = sourceDir.rename (sourcePath, targetPath);
        }
      else
        {
        QFile f(sourcePath);
        ok = f.rename (targetPath);
        }
      if (ok)
        {
        emit statusUpdate (tr("Renamed") + " " + sourcePath + " " 
          + tr("to") + " " + targetPath);
        emit dirContentsChanged();
        }
      else
        {
        QString msg = (tr("Failed to rename") + " " + sourcePath + " " 
          + tr("to") + " " + targetPath);
        emit statusUpdate (msg);
        error (msg);
        }
      }
    }
  }

