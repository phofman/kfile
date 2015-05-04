#pragma once

#include <QObject>
#include <QString>
#include <QLabel>
#include <QListWidget>
#include <QIcon>
#include <QToolBar>
#include <QAction>
#include <QTextEdit>
#include <QMenu>

class KTextEditor : public QWidget
    {
    Q_OBJECT

    public:

    KTextEditor(bool readOnly, QWidget *parent = 0);
    ~KTextEditor(void);

    void loadFile (const QString &fileName, bool isHtml);
    bool saveFile (void);

    signals:
  
    void closeRequested (QWidget *self);
    void tabTitleChanged (QWidget *widget, const QString *title);
    void settingsRequested (void);
    void newBrowserRequested (const QString *path);
    void aboutRequested (void);
    void manualRequested (void);
    void statusUpdate (const QString &text); 

    private slots:

    void handleExitAction (void);
    void handleSaveAction (void);
    void handleSettingsAction (void);
    void handleNewBrowserAction (void);
    void handleManualAction (void);
    void handleAboutAction (void);

    protected:

    void error (const QString &message);
    void message (const QString &message);

    QString path;
    QIcon *exitIcon;
    QIcon *settingsIcon;
    QIcon *saveIcon;
    QIcon *cutIcon;
    QIcon *copyIcon;
    QIcon *pasteIcon;
    QIcon *newBrowserIcon;
    QIcon *helpIcon;
    QIcon *aboutIcon;
    QIcon *manualIcon;
    QToolBar *toolbar;
    QTextEdit *edit;
    QMenu *editMenu;
    QMenu *newMenu;
    QMenu *helpMenu;
    bool isHtml;
    };

