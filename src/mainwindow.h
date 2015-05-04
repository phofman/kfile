#pragma once

#include <QObject>
#include <QWidget>
#include <QMainWindow>
#include <QApplication>
#include <QTabWidget>
#include "ktexteditor.h" 
#include "kfilebrowser.h" 
#include "kfilesettings.h" 
#include "kfilelist.h" 

class MainWindow : public QMainWindow
    {
    Q_OBJECT

    public:

    MainWindow (QApplication *app);
    void openNewBrowserTab (const QString &dirName="");
    void openFiles (const QStringList &fileNames);
    KTextEditor *openNewTextEditorTab (const QString &filename, bool isHtml,
      bool readOnly);
    void openNewFileListTab (const QStringList &Files);
    KFileList *openNewFileListTab (const QString &title, 
      const QString &caption, const QString &path, const QStringList &names);
    void setSkin (KFSkin skin);

    private slots:

    void tabCloseRequested (QWidget *self);
    void newBrowserRequested (const QString *dirName);
    void tabTitleChanged (QWidget *widget, const QString *title);
    void openFilesRequested (const QStringList &fileNames);
    void statusUpdate (const QString &text);
    void handleSearchFromPath (const QString &path);
    void handlePathDeleted (const QString &path);
    void handleSettingsRequested (void);
    void handleManualRequested (void);
    void handleAboutRequested (void);
    void handleDirContentsChanged (void);

    protected:

    void doFileSearch (const QString &path, const QString &text, 
      KFileList *fileList);
    void _doFileSearch (const QString &path, const QString &name, 
      const QString &text, KFileList *fileList, QProgressDialog &progress);
    void broadcastRefresh (void);

    QApplication *app;
    QTabWidget *tabber; 
    QIcon *dirIcon;
    QIcon *txtIcon;
    };


