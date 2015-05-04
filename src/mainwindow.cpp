#include <QPushButton>
#include <QListWidget>
#include <QMessageBox>
#include <QAction>
#include <QToolBar>
#include <QVBoxLayout>
#include <QFileInfo>
#include <QTabWidget> 
#include <sys/platform.h>
#include <bps/event.h> 
#include <bps/navigator.h> 
#include <QStatusBar> 
#include <QInputDialog>
#include <QProgressDialog>
#include <QDir>
#include <QFileDialog>
#include "mainwindow.h" 
#include "kfilebrowser.h" 
#include "ktexteditor.h" 
#include "kfilelist.h" 
#include "kfiledialogs.h" 
#include "kfilesettings.h" 
#include "kfilesettingsdialog.h" 

#define KF_VERSION "1.0.1"
#define ABOUT_MESSAGE "KFile file manager, version " KF_VERSION "\nCopyright (c)2012 Railway Terrace Software, all rights reserved.\n\nIncorporates Qt version 4.8, copyright (c)2012 Nokia Corp, distributed according to the GNU Lesser General Public Licence"

/*=========================================================================
  Constructor
=========================================================================*/
MainWindow::MainWindow(QApplication *app)
    : QMainWindow ()
  {
  this->app = app;

  dirIcon = new QIcon ("app/native/res/dir_icon.png");
  txtIcon = new QIcon ("app/native/res/txt_icon.png");

  tabber = new QTabWidget ();
  QSize size (32, 32);
  tabber->setIconSize (size);
  openNewBrowserTab ();
  setCentralWidget (tabber);
  setSkin (KFileSettings::getGlobalInstance()->getSkin());
  }

/*=========================================================================
  openNewBrowserTab 
=========================================================================*/
void MainWindow::openNewBrowserTab (const QString &dirName)
  {
  KFileBrowser *browser = new KFileBrowser;
  QObject::connect(browser, SIGNAL(closeRequested(QWidget *)), 
      this, SLOT(tabCloseRequested(QWidget *)));
  QObject::connect(browser, SIGNAL(newBrowserRequested(const QString *)), 
      this, SLOT(newBrowserRequested(const QString *)));
  QObject::connect(browser, 
      SIGNAL(tabTitleChanged(QWidget *, const QString *)), 
      this, SLOT(tabTitleChanged(QWidget *, const QString *)));
  QObject::connect(browser, 
      SIGNAL(openFilesRequested(const QStringList &)), 
      this, SLOT(openFilesRequested(const QStringList &)));
  QObject::connect(browser, 
      SIGNAL(statusUpdate(const QString &)), 
      this, SLOT(statusUpdate(const QString &)));
  QObject::connect(browser, 
      SIGNAL(searchFromPath(const QString &)), 
      this, SLOT(handleSearchFromPath(const QString &)));
  QObject::connect(browser, 
      SIGNAL(pathDeleted(const QString &)), 
      this, SLOT(handlePathDeleted(const QString &)));
  QObject::connect(browser, 
      SIGNAL(settingsRequested(void)), 
      this, SLOT(handleSettingsRequested(void)));
  QObject::connect(browser, 
      SIGNAL(manualRequested(void)), 
      this, SLOT(handleManualRequested(void)));
  QObject::connect(browser, 
      SIGNAL(aboutRequested(void)), 
      this, SLOT(handleAboutRequested(void)));
  QObject::connect(browser, 
      SIGNAL(dirContentsChanged(void)), 
      this, SLOT(handleDirContentsChanged(void)));

  tabber->addTab (browser, *dirIcon, "Files");
  browser->setPath (dirName);
  tabber->setCurrentWidget (browser);
  }

/*=========================================================================
  openNewFileListTab 
=========================================================================*/
KFileList *MainWindow::openNewFileListTab (const QString &title, 
    const QString &caption, const QString &path, const QStringList &names)
  {
  KFileList *list = new KFileList (caption, path);
  QObject::connect(list, SIGNAL(closeRequested(QWidget *)), 
      this, SLOT(tabCloseRequested(QWidget *)));
  QObject::connect(list, SIGNAL(newBrowserRequested(const QString *)), 
      this, SLOT(newBrowserRequested(const QString *)));
  QObject::connect(list, 
      SIGNAL(openFilesRequested(const QStringList &)), 
      this, SLOT(openFilesRequested(const QStringList &)));
  QObject::connect(list, 
      SIGNAL(statusUpdate(const QString &)), 
      this, SLOT(statusUpdate(const QString &)));
  QObject::connect(list, 
      SIGNAL(pathDeleted(const QString &)), 
      this, SLOT(handlePathDeleted(const QString &)));
  QObject::connect(list, 
      SIGNAL(settingsRequested(void)), 
      this, SLOT(handleSettingsRequested(void)));
  QObject::connect(list, 
      SIGNAL(manualRequested(void)), 
      this, SLOT(handleManualRequested(void)));
  QObject::connect(list, 
      SIGNAL(aboutRequested(void)), 
      this, SLOT(handleAboutRequested(void)));
  QObject::connect(list, 
      SIGNAL(dirContentsChanged(void)), 
      this, SLOT(handleDirContentsChanged(void)));

  tabber->addTab (list, *dirIcon, title);
  list->setNames (names);
  tabber->setCurrentWidget (list);
  return list;
  }

/*=========================================================================
  openNewTextEditorTab
=========================================================================*/
KTextEditor *MainWindow::openNewTextEditorTab (const QString &fileName, 
    bool isHtml, bool readOnly)
  {
  KTextEditor *editor = new KTextEditor (readOnly);
  QObject::connect(editor, SIGNAL(closeRequested(QWidget *)), 
      this, SLOT(tabCloseRequested(QWidget *)));
  QObject::connect(editor, 
      SIGNAL(tabTitleChanged(QWidget *, const QString *)), 
      this, SLOT(tabTitleChanged(QWidget *, const QString *)));
  QObject::connect(editor, 
      SIGNAL(settingsRequested(void)), 
      this, SLOT(handleSettingsRequested(void)));
  QObject::connect(editor, SIGNAL(newBrowserRequested(const QString *)), 
      this, SLOT(newBrowserRequested(const QString *)));
  QObject::connect(editor, 
      SIGNAL(manualRequested(void)), 
      this, SLOT(handleManualRequested(void)));
  QObject::connect(editor, 
      SIGNAL(aboutRequested(void)), 
      this, SLOT(handleAboutRequested(void)));
  QObject::connect(editor, 
      SIGNAL(statusUpdate(const QString &)), 
      this, SLOT(statusUpdate(const QString &)));

  tabber->addTab (editor, *txtIcon, "Text");
  editor->loadFile (fileName, isHtml);
  tabber->setCurrentWidget (editor);
  return editor;
  }

/*=========================================================================
  slot: tabCloseRequested 
=========================================================================*/
void MainWindow::tabCloseRequested (QWidget *widget)
  {
  if (tabber->count() == 1) 
    {
    if (KFileSettings::getGlobalInstance()->getFlags() & KF_CONFIRM_QUIT)
      {
      QMessageBox msgBox;
      msgBox.setText(tr("Confirm quit"));
      msgBox.setInformativeText
        (tr("This will close the KFile application"));
      msgBox.setStandardButtons(QMessageBox::Ok 
             | QMessageBox::Cancel);
      msgBox.setDefaultButton(QMessageBox::Ok);
      int ret = msgBox.exec();
      if (ret == QMessageBox::Ok)
        {
        delete widget;
        app->quit();
        }
      }
    else
      {
      delete widget;
      app->quit();
      }
    }
  else
    delete widget;
  }

/*=========================================================================
  slot: newBrowserRequested 
=========================================================================*/
void MainWindow::newBrowserRequested (const QString *dirName)
  {
  openNewBrowserTab (*dirName); 
  }

/*=========================================================================
  slot: tabTitleChanged 
=========================================================================*/
void MainWindow::tabTitleChanged (QWidget *widget, const QString *title)
  {
  int l = tabber->count();
  for (int i = 0; i < l; i++)
    {
    if (widget == tabber->widget (i))
      {
      tabber->setTabText (i, *title);
      break;
      }
    }  
  }

/*=========================================================================
  openFiles
=========================================================================*/
void MainWindow::openFiles (const QStringList &fileNames)
  {
  if (fileNames.count() == 0) return;
  if (fileNames.count() != 1)
    {
    KFileDialogs::error ("Opening multiple files is not yet supported");
    return;
    }

  QString fileName = fileNames[0];
  if (fileName.endsWith (".txt"))
    {
    openNewTextEditorTab (fileName, false, false);
    }
  else
    {
    char *buff = NULL;
    navigator_open_file (fileName.toUtf8().constData(), &buff);
    if (buff)
      {
      // The message from the OS is gibberish -- ignore
      KFileDialogs::error ("Blackberry OS can't launch this file: " + fileName);
      free (buff);
      }
    }
  }

/*=========================================================================
  openFileRequested
=========================================================================*/
void MainWindow::openFilesRequested (const QStringList &fileNames)
  {
  openFiles (fileNames);
  }

/*=========================================================================
  slot statusUpdate 
=========================================================================*/
void MainWindow::statusUpdate (const QString &text)
  {
  statusBar()->showMessage (text, 3000);
  }

/*=========================================================================
  _doFileSearch 
=========================================================================*/
void MainWindow::_doFileSearch (const QString &path, const QString &name, 
    const QString &text, KFileList *fileList, QProgressDialog &progress)
  {
  QFileInfo info (path + "/" + name);
  if (info.isDir())
    {
    QStringList entries = QDir(path + "/" + name).entryList();
    int l = entries.count();
    for (int i = 0; i < l; i++)
      {
      QString epath = entries[i]; 
      if (epath != "." && epath != ".." && !progress.wasCanceled())
        {
        int v = progress.value();
        v++;
        if (v == 100) v = 0;
        progress.setValue (v);
        if (name == "")
          _doFileSearch (path, epath, text, fileList, progress);
        else
          _doFileSearch (path, name + "/" + epath, text, fileList, progress);
        }
      }
    }
  else
    {
    if (name.contains (text, Qt::CaseInsensitive))
      fileList->addName (name);
    }
  }

/*=========================================================================
  doFileSearch 
=========================================================================*/
void MainWindow::doFileSearch (const QString &path, const QString &text, 
    KFileList *fileList)
  {
  QProgressDialog progress (tr("Searching..."), tr("Stop"), 
      0, 100, this);
  progress.setWindowModality (Qt::WindowModal);
  progress.setMinimumDuration (0);
  progress.show();

  _doFileSearch (path, "", text, fileList, progress);

  progress.setValue (100);
  }

/*=========================================================================
  slot handleSearchFromPath 
=========================================================================*/
void MainWindow::handleSearchFromPath (const QString &path) 
  {
  bool ok = false;
  QString text = QInputDialog::getText (this, tr("Search"),
    tr("Find files with name:"), QLineEdit::Normal, "", &ok);
  if (ok && !text.isEmpty())
    {
    QStringList dummy;
    KFileList *fileList = 
      openNewFileListTab (tr("Search"), tr("Filenames containing") 
        + " " + text + " " + tr("in") + " " + path, path, dummy);

    doFileSearch (path, text, fileList); 
    } 
  }

/*=========================================================================
  slot broadcastRefresh 
=========================================================================*/
void MainWindow::broadcastRefresh (void) 
  {
  int l = tabber->count();
  for (int i = 0; i < l; i++)
    {
    QWidget *widget = tabber->widget (i);
    if (widget->inherits ("KFileWidget"))
      {
      KFileWidget *kfw = (KFileWidget*) widget;
      kfw->refresh();
      }
    }  
  }

/*=========================================================================
  slot handlePathDeleted
=========================================================================*/
void MainWindow::handlePathDeleted (const QString &path) 
  {
  int l = tabber->count();
  for (int i = 0; i < l; i++)
    {
    QWidget *widget = tabber->widget (i);
    if (widget->inherits ("KFileWidget"))
      {
      KFileWidget *kfw = (KFileWidget*) widget;
      kfw->notifyPathDeleted (path);
      }
    }  
  }

/*=========================================================================
  handleSettingsRequested 
=========================================================================*/
void MainWindow::setSkin (KFSkin skin)
  {
  switch (skin)
    {
    case KF_SKIN_LIGHT:
      app->setStyleSheet ("QToolButton { border: 0px; padding: 5px; } "
   "QWidget { }" 
   "QToolButton { }" 
   "QPushButton { height: 48px; }" 
   "KFileWidget { }" 
   "QLabel#pathDisplay { } "
   "QLabel#captionDisplay { } "
   "QScrollBar { } "
   "QDialog {  border: 2px solid grey; } "
   "QRadioButton {  spacing: 20px; } "
   "QMenu {  border: 1px solid black; } "
   "QMenu::item {  height: 58px; } "
   "QMenu::separator{ height: 1px; background: black; } "
   "QRadioButton::indicator:checked { } "
   "QRadioButton::indicator:!checked { } "
   "QToolBar { } ");
      break;

    case KF_SKIN_DARK:
      app->setStyleSheet ("QToolButton { border: 0px; padding: 5px; } "
   "QWidget { background-color: black; color: white; }" 
   "QToolButton { background-color: #202020; color: white; }" 
   "QPushButton { background-color: #202020; color: white; height: 48px; }" 
   "KFileWidget { background-color: blue; color: white; }" 
   "QLabel#pathDisplay { background-color: #202020; color: white; border: 1px groove gray; } "
   "QLabel#captionDisplay { background-color: #202020; color: white; border: 1px groove gray; } "
   "QScrollBar { background: #202020; border: 1px solid grey; } "
   "QDialog {  border: 2px solid grey; } "
   "QRadioButton {  spacing: 20px; } "
   "QMenu {  border: 1px solid white; } "
   "QMenu::item { } "
   "QMenu::separator{ height: 1px; background: white; } "
   "QRadioButton::indicator:checked {  color: red; background: red; background-color: red; } "
   "QRadioButton::indicator:!checked {  color: white; background: white; background-color: white; } "
   "QToolBar { background-color: #202020; color: white; border: 1px groove gray; } ");
      break;
    }
  }

/*=========================================================================
  handleSettingsRequested 
=========================================================================*/
void MainWindow::handleSettingsRequested (void)
  {
  KFileSettings newSettings;
  KFileSettings *globalSettings = KFileSettings::getGlobalInstance();
  newSettings.set (globalSettings);
  KFileSettingsDialog d (this, &newSettings);
  if (d.exec() == QDialog::Accepted)
    {
    if (newSettings.getSkin() != globalSettings->getSkin())
      {
      setSkin (newSettings.getSkin());
      }
    globalSettings->set (&newSettings);
    globalSettings->save ();
    }
  }

/*=========================================================================
  handleAboutRequested 
=========================================================================*/
void MainWindow::handleAboutRequested (void)
  {
  QIcon icon ("app/native/res/icon.png");
  QMessageBox msgBox (QMessageBox::NoIcon, tr("About"),
    ABOUT_MESSAGE, QMessageBox::Ok, this);
  msgBox.setIconPixmap (icon.pixmap (64, 64));
  msgBox.exec();
  }

/*=========================================================================
  handleManualRequested 
=========================================================================*/
void MainWindow::handleManualRequested (void)
  {
  KTextEditor *editor = openNewTextEditorTab 
    ("app/native/res/kfile_manual.htm", true, true);
  }

/*=========================================================================
  handleDirContentsChanged
=========================================================================*/
void MainWindow::handleDirContentsChanged (void)
  {
  broadcastRefresh();
  }

