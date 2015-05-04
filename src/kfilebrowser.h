#pragma once

#include <QObject>
#include <QString>
#include <QLabel>
#include <QListWidget>
#include <QIcon>
#include <QToolBar>
#include <QAction>
#include <QProgressDialog>
#include <QToolButton>
#include "fileclipboard.h" 
#include "kfilewidget.h" 

class KFileBrowser : public KFileWidget
    {
    Q_OBJECT

    public:

    KFileBrowser(QWidget *parent = 0);
    ~KFileBrowser(void);

    void setPath (const QString &path);
    void refresh (void);
    QString getCurrentItem (void) const;
    void up (void);
    static QString getHomeDir (void);

    signals:
  
    void closeRequested (QWidget *self);
    void newBrowserRequested (const QString *dirName);
    void tabTitleChanged (QWidget *widget, const QString *title);
    void searchFromPath (const QString &path); 

    private slots:

    void handleUpAction (void);
    void handleHomeAction (void);
    void handleViewAction (void);
    void handleExitAction (void);
    void handleNewBrowserAction (void);
    void handleNewFileAction (void);
    void handleNewDirAction (void);
    void handlePasteAction (void);
    void handleRefreshAction (void);
    void handleSearchAction (void);
    void handleRenameAction (void);

    protected:

    virtual void openSingleDir (const QString &dirName);
    bool copyFromClipboard (const FileClipboard *fc);
    bool cutFromClipboard (const FileClipboard *fc);
    static KFileCategory classifyFileByName 
      (const QString &fileName);

    QLabel *pathDisplay;
    QString homeDir;
    QToolBar *toolbar;
    QMenu *newMenu;
    QMenu *editMenu;
    QMenu *helpMenu;
    };

