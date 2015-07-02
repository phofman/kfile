#include <QtGui/QApplication>
#include <QtGui/QPushButton>
#include <QtGui/QWidget>
#include <QtGui/QListWidget>
#include <QtCore/QDir>
#include <QtGui/QMessageBox>
#include <QtGui/QVBoxLayout>
#include <QtGui/QAction>
#include <QtGui/QToolBar>
#include <QtGui/QAbstractItemView>
#include <QtGui/QTextEdit>
#include <QtCore/QTextStream>
#include <QtGui/QToolButton>

#include "ktexteditor.h"

/*=========================================================================
  Constructor
=========================================================================*/
KTextEditor::KTextEditor(bool readOnly, QWidget *parent)
    : QWidget(parent), path("")
{
    isHtml = false;

    QLayout *layout = new QVBoxLayout;

    exitIcon = new QIcon("app/native/res/exit_icon.png");
    saveIcon = new QIcon("app/native/res/save_icon.png");
    cutIcon = new QIcon("app/native/res/cut_icon.png");
    copyIcon = new QIcon("app/native/res/copy_icon.png");
    pasteIcon = new QIcon("app/native/res/paste_icon.png");
    settingsIcon = new QIcon("app/native/res/settings_icon.png");
    newBrowserIcon = new QIcon("app/native/res/newbrowser_icon.png");
    helpIcon = new QIcon("app/native/res/help_icon.png");
    aboutIcon = new QIcon("app/native/res/about_icon.png");
    manualIcon = new QIcon("app/native/res/manual_icon.png");

    toolbar = new QToolBar();
    toolbar->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

    edit = new QTextEdit();

    QAction *exitAction = new QAction(*exitIcon, "E&xit", toolbar);
    QObject::connect(exitAction, SIGNAL(triggered(bool)),
        this, SLOT(handleExitAction()));

    QAction *saveAction = new QAction(*saveIcon, "&Save", toolbar);
    QObject::connect(saveAction, SIGNAL(triggered(bool)),
        this, SLOT(handleSaveAction()));

    QAction *cutAction = new QAction(*cutIcon, "&Cut",
        toolbar);
    QObject::connect(cutAction, SIGNAL(triggered(bool)),
        edit, SLOT(cut()));

    QAction *copyAction = new QAction(*copyIcon, "&Copy",
        toolbar);
    QObject::connect(copyAction, SIGNAL(triggered(bool)),
        edit, SLOT(copy()));

    QAction *pasteAction = new QAction(*pasteIcon, "&Paste",
        toolbar);
    QObject::connect(pasteAction, SIGNAL(triggered(bool)),
        edit, SLOT(paste()));

    QAction *settingsAction = new QAction(*settingsIcon, "Settings",
        toolbar);
    QObject::connect(settingsAction, SIGNAL(triggered(bool)),
        this, SLOT(handleSettingsAction()));

    QAction *newBrowserAction = new QAction(*newBrowserIcon, "New browser",
        toolbar);
    QObject::connect(newBrowserAction, SIGNAL(triggered(bool)),
        this, SLOT(handleNewBrowserAction()));

    QAction *manualAction = new QAction(*manualIcon, "Manual",
        toolbar);
    QObject::connect(manualAction, SIGNAL(triggered(bool)),
        this, SLOT(handleManualAction()));

    QAction *aboutAction = new QAction(*aboutIcon, "About",
        toolbar);
    QObject::connect(aboutAction, SIGNAL(triggered(bool)),
        this, SLOT(handleAboutAction()));

    newMenu = new QMenu();
    QToolButton *newButton = new QToolButton();
    newMenu->addAction(newBrowserAction);
    newButton->setMenu(newMenu);
    newButton->setIcon(*newBrowserIcon);
    newButton->setPopupMode(QToolButton::InstantPopup);
    newButton->setText("New");
    newButton->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

    editMenu = new QMenu();
    QToolButton *editButton = new QToolButton();
    editMenu->addAction(cutAction);
    editMenu->addAction(copyAction);
    editMenu->addAction(pasteAction);
    editButton->setMenu(editMenu);
    editButton->setIcon(*copyIcon);
    editButton->setPopupMode(QToolButton::InstantPopup);
    editButton->setText("Edit");
    editButton->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

    helpMenu = new QMenu();
    QToolButton *helpButton = new QToolButton();
    helpMenu->addAction(manualAction);
    helpMenu->addAction(aboutAction);
    helpButton->setMenu(helpMenu);
    helpButton->setIcon(*helpIcon);
    helpButton->setPopupMode(QToolButton::InstantPopup);
    helpButton->setText("Help");
    helpButton->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

    toolbar->addAction(exitAction);
    toolbar->addAction(saveAction);
    toolbar->addWidget(newButton);
    toolbar->addWidget(editButton);
    toolbar->addAction(settingsAction);
    toolbar->addWidget(helpButton);

    layout->addWidget(toolbar);
    layout->addWidget(edit);

    if (readOnly)
    {
        cutAction->setDisabled(true);
        pasteAction->setDisabled(true);
        saveAction->setDisabled(true);
        edit->setReadOnly(true);
    }

    setLayout(layout);
}

/*=========================================================================
  Destructor
=========================================================================*/
KTextEditor::~KTextEditor()
{
    if (edit) delete edit;
    if (settingsIcon) delete settingsIcon;
    if (helpIcon) delete helpIcon;
    if (aboutIcon) delete aboutIcon;
    if (manualIcon) delete manualIcon;
    if (exitIcon) delete exitIcon;
    if (saveIcon) delete saveIcon;
    if (cutIcon) delete cutIcon;
    if (copyIcon) delete copyIcon;
    if (pasteIcon) delete pasteIcon;
    if (newBrowserIcon) delete newBrowserIcon;
    if (editMenu) delete editMenu;
    if (newMenu) delete newMenu;
    if (helpMenu) delete helpMenu;
    if (toolbar) delete toolbar;
}

/*=========================================================================
  message
=========================================================================*/
void KTextEditor::message(const QString &message)
{
    QMessageBox msgBox;
    msgBox.setText(message);
    msgBox.exec();
}

/*=========================================================================
  error 
=========================================================================*/
void KTextEditor::error(const QString &message)
{
    QMessageBox msgBox;
    msgBox.setText(message);
    msgBox.setIcon(QMessageBox::Critical);
    msgBox.setWindowTitle(tr("Error"));
    msgBox.exec();
}

/*=========================================================================
  loadFile
=========================================================================*/
void KTextEditor::loadFile(const QString &fileName, bool isHtml)
{
    QFile file(fileName);
    if (file.exists())
    {
        if (file.open(QIODevice::ReadOnly))
        {
            QTextStream in(&file);
            QString s = in.readAll();
            if (isHtml)
                edit->setHtml(s);
            else
                edit->setPlainText(s);
            file.close();
            path = fileName;
            QString title = tr("Text: ") + QFileInfo(this->path).fileName();
            emit tabTitleChanged((QWidget *)this, &title);
            this->isHtml = isHtml;
        }
        else
        {
            error(tr("Can't open file for reading: ") + fileName);
        }
    }
    else
    {
        error(tr("No such file: ") + fileName);
    }
}

/*=========================================================================
  saveFile
=========================================================================*/
bool KTextEditor::saveFile(void)
{
    bool ret = false;
    QFile file(path);
    if (file.exists())
    {
        if (file.open(QIODevice::WriteOnly))
        {
            QTextStream out(&file);
            if (isHtml)
                out << edit->document()->toHtml();
            else
                out << edit->document()->toPlainText();
            edit->document()->setModified(false);
            emit statusUpdate(tr("Wrote file") + " " +
                path);
            file.close();
            ret = true;
        }
        else
        {
            error(tr("Can't open file for writing: ") + path);
        }
    }
    else
    {
        error(tr("No such file: ") + path);
    }
    return ret;
}

/*=========================================================================
  slot handleExitAction 
=========================================================================*/
void KTextEditor::handleExitAction(void)
{
    bool canClose = true;
    if (edit->document()->isModified())
    {
        canClose = false;
        QMessageBox msgBox;
        msgBox.setText(tr("The document has been modified."));
        msgBox.setInformativeText(tr("Do you want to save your changes?"));
        msgBox.setStandardButtons(QMessageBox::Save
            | QMessageBox::Discard | QMessageBox::Cancel);
        msgBox.setDefaultButton(QMessageBox::Save);
        int ret = msgBox.exec();
        switch (ret)
        {
        case QMessageBox::Save:
            canClose = saveFile();
            break;
        case QMessageBox::Discard:
            canClose = true;
            break;
        case QMessageBox::Cancel:
            canClose = false;
            break;
        }
    }
    if (canClose)
        emit closeRequested(this);
}

/*=========================================================================
  slot handleSaveAction 
=========================================================================*/
void KTextEditor::handleSaveAction(void)
{
    saveFile();
}
  
/*=========================================================================
  slot handleSettingsAction 
=========================================================================*/
void KTextEditor::handleSettingsAction(void)
{
    emit settingsRequested();
}

/*=========================================================================
  slot newBrowserAction 
=========================================================================*/
void KTextEditor::handleNewBrowserAction(void)
{
    QString empty;
    emit newBrowserRequested(&empty);
}

/*=========================================================================
  slot handleAboutAction 
=========================================================================*/
void KTextEditor::handleAboutAction(void)
{
    emit aboutRequested();
}

/*=========================================================================
  slot handleManualAction 
=========================================================================*/
void KTextEditor::handleManualAction(void)
{
    emit manualRequested();
}

