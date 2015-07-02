#pragma once

#include <QObject>
#include <QtGui/QWidget>
#include <QtGui/QProgressDialog>
#include <QtGui/QListWidget>
#include <QtGui/QIcon>
#include "kineticscroller.h"

typedef enum
{
    FCAT_UNKNOWN = 0,
    FCAT_COMPRESSED,
    FCAT_MEDIA_AUDIO,
    FCAT_MEDIA_VIDEO,
    FCAT_DOC_PDF,
    FCAT_DOC_OFFICE,
    FCAT_MEDIA_EBOOK,
    FCAT_DOC_HTML,
    FCAT_DOC_TXT,
    FCAT_MEDIA_IMAGE
} KFileCategory;

class KFileWidget : public QWidget
{
    Q_OBJECT

public:

    typedef enum
    {
        List = 0,
        GridSmallIcons,
        GridLargeIcons,
        NumViewModes
    } ViewMode;

    ~KFileWidget(void);
    KFileWidget(const QString &path, QWidget *parent);
    static KFileCategory classifyFileByName(const QString &fileName);
    QStringList getSelectedItems(void) const;
    void notifyPathDeleted(const QString &pathName);
    virtual void refresh(void) = 0;

signals:

    void pathDeleted(const QString &path);
    void statusUpdate(const QString &text);
    void openFilesRequested(const QStringList &fileNames);
    void settingsRequested(void);
    void aboutRequested(void);
    void manualRequested(void);
    void dirContentsChanged(void);

    protected slots:

    void handleOpenAction(void);
    void handleDeleteAction(void);
    void itemDoubleClicked(QListWidgetItem * item);
    void itemActivated(QListWidgetItem * item);
    void handleCopyAction(void);
    void handleCutAction(void);
    void handleSettingsAction(void);
    void handleManualAction(void);
    void handleAboutAction(void);
    void handleSelectAllAction(void);
    void handleSelectNoneAction(void);
    void toggleViewMode(void);
    void setViewMode(ViewMode viewMode);

protected:

    virtual void openSingleDir(const QString &dirName) = 0;
    void openFilesOrDirs(const QStringList &fileNames);
    void createIcons();
    void deleteIcons();
    void error(const QString &message, QWidget *parent = 0);
    void message(const QString &message, QWidget *parent = 0);
    const QIcon &getIconForFile(const QString &fileName);
    QStringList expandNames(const QString &root, const QStringList &names, bool *cancelled, bool dirBeforeFiles);
    QStringList _expandNames(const QString &root, const QString &path, QProgressDialog *progress, bool dirBeforeFiles);
    bool deleteFileOrDir(const QString &filename);

    QListWidget *list;
    QString path;
    QIcon *fileIcon;
    QIcon *dirIcon;
    QIcon *dirLinkIcon;
    QIcon *exitIcon;
    QIcon *openIcon;
    QIcon *upIcon;
    QIcon *homeIcon;
    QIcon *viewIcon;
    QIcon *newBrowserIcon;
    QIcon *newFileIcon;
    QIcon *newDirIcon;
    QIcon *deleteIcon;
    QIcon *cutIcon;
    QIcon *copyIcon;
    QIcon *pasteIcon;
    QIcon *refreshIcon;
    QIcon *audioIcon;
    QIcon *videoIcon;
    QIcon *pdfIcon;
    QIcon *officeIcon;
    QIcon *ebookIcon;
    QIcon *htmlIcon;
    QIcon *txtIcon;
    QIcon *zipIcon;
    QIcon *imageIcon;
    QIcon *searchIcon;
    QIcon *settingsIcon;
    QIcon *helpIcon;
    QIcon *aboutIcon;
    QIcon *manualIcon;
    QIcon *renameIcon;
    QIcon *selectAllIcon;
    QIcon *selectNoneIcon;
    bool pasteByNameOnly;
    ViewMode viewMode;
    KineticScroller *kineticScroller;
};


