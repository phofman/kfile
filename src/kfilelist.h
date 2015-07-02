#pragma once

#include <QtCore/QObject>
#include <QtCore/QString>
#include <QtGui/QLabel>
#include <QtGui/QListWidget>
#include <QtGui/QIcon>
#include <QtGui/QToolBar>
#include <QtGui/QAction>
#include <QtGui/QProgressDialog>
#include <QtGui/QToolButton>

#include "fileclipboard.h" 
#include "kfilewidget.h" 

class KFileList : public KFileWidget
{
    Q_OBJECT

public:

    KFileList(const QString &caption, const QString &path,
        QWidget *parent = 0);
    ~KFileList(void);

    void setNames(const QStringList &names);
    void addName(const QString &name);

signals:

    void closeRequested(QWidget *self);
    void newBrowserRequested(const QString *path);

    private slots:

    void handleExitAction(void);
    void handleNewBrowserAction(void);

protected:

    virtual void openSingleDir(const QString &dirName);
    void refresh(void);

    QToolBar *toolbar;
    QMenu *editMenu;
    QMenu *newMenu;
    QMenu *helpMenu;
    QLabel *captionDisplay;
};

