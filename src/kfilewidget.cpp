#include <unistd.h> 
#include <QtGui/QApplication>
#include <QtGui/QPushButton>
#include <QtGui/QWidget>
#include <QtGui/QListWidget>
#include <QtCore/QDir>
#include <QtCore/QStringList>
#include <QtGui/QMessageBox>
#include <QtGui/QVBoxLayout>
#include <QtGui/QAction>
#include <QtGui/QToolBar>
#include <QtGui/QAbstractItemView>
#include <QtGui/QInputDialog>
#include <QtGui/QProgressDialog>
#include <QtGui/QToolButton>
#include <QtGui/QMenu>

#include "fileclipboard.h"
#include "kfilesettings.h"
#include "kfilewidget.h"
#include "kfileinfo.h"
#include "jpegthumbnailfetcher.h"
#include "kineticscroller.h"

/*=========================================================================
  constructor 
=========================================================================*/
KFileWidget::KFileWidget(const QString &path, QWidget *parent)
    : QWidget(parent)
{
    createIcons();
    this->path = path;
    list = new QListWidget();
    list->grabGesture(Qt::SwipeGesture);
    list->setSelectionMode(QAbstractItemView::MultiSelection);
    list->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
    setViewMode(List);
    connect(list, SIGNAL(itemDoubleClicked(QListWidgetItem *)),
        this, SLOT(itemDoubleClicked(QListWidgetItem *)));
    connect(list, SIGNAL(itemClicked(QListWidgetItem *)),
        this, SLOT(itemActivated(QListWidgetItem *)));
    pasteByNameOnly = false;
    kineticScroller = new KineticScroller;
    kineticScroller->enableKineticScrollFor(list);
}

/*=========================================================================
  destructor 
=========================================================================*/
KFileWidget::~KFileWidget(void)
{
    if (list) delete list;
    if (kineticScroller) delete kineticScroller;
    deleteIcons();
}

/*=========================================================================
  createIcons
=========================================================================*/
void KFileWidget::createIcons(void)
{
    renameIcon = new QIcon("app/native/res/rename_icon.png");
    fileIcon = new QIcon("app/native/res/file_icon.png");
    fileIcon = new QIcon("app/native/res/file_icon.png");
    dirIcon = new QIcon("app/native/res/dir_icon.png");
    dirLinkIcon = new QIcon("app/native/res/dirlink_icon.png");
    exitIcon = new QIcon("app/native/res/exit_icon.png");
    openIcon = new QIcon("app/native/res/open_icon.png");
    upIcon = new QIcon("app/native/res/up_icon.png");
    homeIcon = new QIcon("app/native/res/home_icon.png");
    viewIcon = new QIcon("app/native/res/view_icon.png");
    newBrowserIcon = new QIcon("app/native/res/newbrowser_icon.png");
    newFileIcon = new QIcon("app/native/res/newfile_icon.png");
    newDirIcon = new QIcon("app/native/res/newdir_icon.png");
    deleteIcon = new QIcon("app/native/res/delete_icon.png");
    cutIcon = new QIcon("app/native/res/cut_icon.png");
    copyIcon = new QIcon("app/native/res/copy_icon.png");
    pasteIcon = new QIcon("app/native/res/paste_icon.png");
    refreshIcon = new QIcon("app/native/res/refresh_icon.png");
    audioIcon = new QIcon("app/native/res/audio_icon.png");
    videoIcon = new QIcon("app/native/res/video_icon.png");
    pdfIcon = new QIcon("app/native/res/pdf_icon.png");
    officeIcon = new QIcon("app/native/res/office_icon.png");
    ebookIcon = new QIcon("app/native/res/ebook_icon.png");
    htmlIcon = new QIcon("app/native/res/html_icon.png");
    txtIcon = new QIcon("app/native/res/txt_icon.png");
    zipIcon = new QIcon("app/native/res/zip_icon.png");
    imageIcon = new QIcon("app/native/res/image_icon.png");
    searchIcon = new QIcon("app/native/res/search_icon.png");
    settingsIcon = new QIcon("app/native/res/settings_icon.png");
    helpIcon = new QIcon("app/native/res/help_icon.png");
    aboutIcon = new QIcon("app/native/res/about_icon.png");
    manualIcon = new QIcon("app/native/res/manual_icon.png");
    selectAllIcon = new QIcon("app/native/res/selectall_icon.png");
    selectNoneIcon = new QIcon("app/native/res/selectnone_icon.png");
}

/*=========================================================================
  deleteIcons
=========================================================================*/
void KFileWidget::deleteIcons(void)
{
    if (selectAllIcon) delete selectAllIcon;
    if (selectNoneIcon) delete selectNoneIcon;
    if (renameIcon) delete renameIcon;
    if (fileIcon) delete fileIcon;
    if (dirIcon) delete dirIcon;
    if (dirLinkIcon) delete dirLinkIcon;
    if (exitIcon) delete exitIcon;
    if (openIcon) delete openIcon;
    if (upIcon) delete upIcon;
    if (homeIcon) delete homeIcon;
    if (viewIcon) delete viewIcon;
    if (newFileIcon) delete newFileIcon;
    if (newDirIcon) delete newDirIcon;
    if (newBrowserIcon) delete newBrowserIcon;
    if (deleteIcon) delete deleteIcon;
    if (cutIcon) delete cutIcon;
    if (copyIcon) delete copyIcon;
    if (pasteIcon) delete pasteIcon;
    if (refreshIcon) delete refreshIcon;
    if (audioIcon) delete audioIcon;
    if (videoIcon) delete videoIcon;
    if (pdfIcon) delete pdfIcon;
    if (officeIcon) delete officeIcon;
    if (ebookIcon) delete ebookIcon;
    if (htmlIcon) delete htmlIcon;
    if (txtIcon) delete txtIcon;
    if (zipIcon) delete zipIcon;
    if (imageIcon) delete imageIcon;
    if (searchIcon) delete searchIcon;
    if (helpIcon) delete helpIcon;
    if (aboutIcon) delete aboutIcon;
    if (manualIcon) delete manualIcon;
}

/*=========================================================================
  classifyFileByName
=========================================================================*/
KFileCategory KFileWidget::classifyFileByName(const QString &fileName)
{
    QFileInfo info(fileName);
    QString ext = info.suffix().toLower();

    if (ext == "gz" || ext == "zip" || ext == "rar" || ext == "7z" ||
        ext == "z")
        return FCAT_COMPRESSED;

    if (ext == "mp3" || ext == "wma" || ext == "aac" || ext == "m4a"
        || ext == "ogg" || ext == "oga" || ext == "flac")
        return FCAT_MEDIA_AUDIO;

    if (ext == "avi" || ext == "m4v" || ext == "ogv" || ext == "wmv"
        || ext == "mp4")
        return FCAT_MEDIA_VIDEO;

    if (ext == "pdf") return FCAT_DOC_PDF;

    if (ext == "doc" || ext == "docx" || ext == "xls") return FCAT_DOC_OFFICE;

    if (ext == "epub" || ext == "mobi" || ext == "cbz" || ext == "cbr")
        return FCAT_MEDIA_EBOOK;

    if (ext == "html" || ext == "htm") return FCAT_DOC_HTML;

    if (ext == "txt" || ext == "asc") return FCAT_DOC_TXT;

    if (ext == "png" || ext == "jpg" || ext == "gif" || ext == "bmp")
        return FCAT_MEDIA_IMAGE;

    return FCAT_UNKNOWN;
}

/*=========================================================================
  getIconForFile 
=========================================================================*/
const QIcon &KFileWidget::getIconForFile(const QString &fileName)
{
    QFileInfo info(fileName);
    if (info.isDir())
    {
        if (info.isSymLink())
            return *dirLinkIcon;
        else
            return *dirIcon;
    }
    else
    {
        KFileCategory cat = classifyFileByName(fileName);
        switch (cat)
        {
        case FCAT_COMPRESSED:
            return *zipIcon;
        case FCAT_MEDIA_AUDIO:
            return *audioIcon;
        case FCAT_MEDIA_VIDEO:
            return *videoIcon;
        case FCAT_DOC_PDF:
            return *pdfIcon;
        case FCAT_DOC_OFFICE:
            return *officeIcon;
        case FCAT_MEDIA_EBOOK:
            return *ebookIcon;
        case FCAT_DOC_HTML:
            return *htmlIcon;
        case FCAT_DOC_TXT:
            return *txtIcon;
        case FCAT_MEDIA_IMAGE:
        {
            if (KFileSettings::getGlobalInstance()->getFlags() & KF_JPEG_THUMBNAILS)
            {
                if (fileName.endsWith(".jpg", Qt::CaseInsensitive) ||
                    fileName.endsWith("*.jpeg", Qt::CaseInsensitive))
                {
                    // We'd better hope that the Qt reference-counting thing comes
                    //  into play here, because otherwise we've got a colossal
                    //  memory leak. We can't free this icon, since it ends up 
                    //  buried inside the list widget somewhere
                    QIcon *i = JpegThumbnailFetcher::fetchThumbnailAsIcon(fileName);
                    return *i;
                }
                else
                    return *imageIcon;
            }
            else
                return *imageIcon;
        }
        default:
            return *fileIcon;
        }
    }
}

/*=========================================================================
  message
=========================================================================*/
void KFileWidget::message(const QString &message, QWidget *parent)
{
    if (parent == 0) parent = this;
    QMessageBox msgBox(parent);
    msgBox.setText(message);
    msgBox.exec();
}

/*=========================================================================
  error 
=========================================================================*/
void KFileWidget::error(const QString &message, QWidget *parent)
{
    if (parent == 0) parent = this;
    QMessageBox msgBox(parent);
    msgBox.setText(message);
    msgBox.setIcon(QMessageBox::Critical);
    msgBox.setWindowTitle(tr("Error"));
    msgBox.exec();
}

/*=========================================================================
  slot handleDeleteAction 
=========================================================================*/
void KFileWidget::handleDeleteAction(void)
{
    QStringList names = getSelectedItems();
    // Note that names is a list of names, not of paths
    if (names.count() == 0)
    {
        message(tr("Select files or folders to delete first."));
    }
    else
    {
        bool cancelled = false;
        QStringList expandedNames = expandNames(path, names, &cancelled,
            false);
        // expanded names is a list of files relative to the current value
        //  of this->path
        if (!cancelled)
        {
            if (expandedNames.count() > 0)
            {
                bool doDelete = false;
                if (KFileSettings::getGlobalInstance()->getFlags() & KF_CONFIRM_DELETE)
                {
                    QMessageBox msgBox;
                    msgBox.setText(tr("Confirm delete"));
                    if (expandedNames.count() == 1)
                    {
                        msgBox.setInformativeText(tr("Delete") + " "
                            + expandedNames[0] + "?");
                    }
                    else
                    {
                        char s[20];
                        sprintf(s, "%d", expandedNames.count());
                        msgBox.setInformativeText(tr("Delete these") + " " +
                            s + " " + tr("items") + "?");
                    }
                    msgBox.setStandardButtons(QMessageBox::Ok
                        | QMessageBox::Cancel);
                    msgBox.setDefaultButton(QMessageBox::Cancel);
                    int ret = msgBox.exec();
                    if (ret == QMessageBox::Ok)
                        doDelete = true;
                }
                else
                    doDelete = true;
                if (doDelete)
                {
                    int l = expandedNames.count();
                    QProgressDialog progress(tr("Deleting files..."), tr("Stop"),
                        0, expandedNames.count(), this);
                    progress.setWindowModality(Qt::WindowModal);
                    progress.setMinimumDuration(0);
                    for (int i = 0; i < l && !progress.wasCanceled(); i++)
                    {
                        QString toDelete =
                            path + "/" + expandedNames[i];
                        if (deleteFileOrDir(toDelete))
                        {
                            emit statusUpdate(tr("Deleted") + " " +
                                toDelete);
                            emit pathDeleted(toDelete);
                        }
                        else
                        {
                            // TODO abort/continue
                            error(tr("Could not delete") + " " + toDelete);
                            emit statusUpdate(tr("Could not delete") + " " +
                                toDelete);
                        }
                        progress.setValue(i);
                    }
                    progress.setValue(l);
                    emit dirContentsChanged();
                }
            }
        }
    }
}

/*=========================================================================
  getSelectedItems 
  Returns the selected paths, before expansion. The list may be
  empty. 
  NOTE NOTE NOTE The returned list is of names only, not paths. The
  names will be files or directories relative to the current value
  of this->path
=========================================================================*/
QStringList KFileWidget::getSelectedItems(void) const
{
    QStringList pathList;

    QList<QListWidgetItem *> items = list->selectedItems();
    int l = items.count();
    for (int i = 0; i < l; i++)
    {
        QListWidgetItem *item = items[i];
        pathList.append(item->text());
    }

    return pathList;
}

/*=========================================================================
  _expandPaths
=========================================================================*/
QStringList KFileWidget::_expandNames(const QString &root,
    const QString &path, QProgressDialog *progress, bool dirBeforeFiles)
{
    QStringList list;

    QFileInfo info(root + "/" + path);

    if (info.isDir())
    {
        QStringList entries = QDir(root + "/" + path).entryList();
        int l = entries.count();
        if (dirBeforeFiles)
            list.append(path);
        for (int i = 0; i < l; i++)
        {
            QString epath = entries[i];
            if (epath != "." && epath != ".." && !progress->wasCanceled())
            {
                QStringList ll = _expandNames(root, path + "/" + epath, progress,
                    dirBeforeFiles);
                list.append(ll);
            }
        }
        if (!dirBeforeFiles)
            list.append(path);
    }
    else
        list.append(path);

    return list;
}

/*=========================================================================
  expandPaths
=========================================================================*/
QStringList KFileWidget::expandNames(const QString &root,
    const QStringList &names, bool *cancelled, bool dirBeforeFiles)
{
    QStringList expandedPaths;
    QProgressDialog progress(tr("Counting files..."), tr("Stop"),
        0, 20, this);
    progress.setWindowModality(Qt::WindowModal);
    progress.setMinimumDuration(0);
    int l = names.count();
    for (int i = 0; i < l && !progress.wasCanceled(); i++)
    {
        QStringList l = _expandNames(root, names[i], &progress, dirBeforeFiles);
        expandedPaths.append(l);
        progress.setValue(i);
    }
    progress.setValue(l);
    *cancelled = progress.wasCanceled();
    return expandedPaths;
}

/*=========================================================================
  slot deleteFileOrDir 
=========================================================================*/
bool KFileWidget::deleteFileOrDir(const QString &fileName)
{
    bool ret = false;
    QFileInfo info(fileName);
    if (!info.isDir())
    {
        QFile f(fileName);
        ret = f.remove();
    }
    else
    {
        QDir d(fileName);
        ret = d.rmdir(fileName);
    }
    return ret;
}

/*=========================================================================
  slot: itemDoubleClicked 
=========================================================================*/
void KFileWidget::itemDoubleClicked(QListWidgetItem * item)
{
    QString name = item->text();
    QStringList paths;
    paths.append(path + "/" + name);
    openFilesOrDirs(paths);
}

/*=========================================================================
  slot: itemActivated
=========================================================================*/
void KFileWidget::itemActivated(QListWidgetItem * item)
{
    QString name = item->text();
    QString pathName = path + "/" + name;
    KFileInfo *info = KFileInfo::getInstance(pathName, KFileInfo::Brief);
    emit statusUpdate(info->statusLineSummary());
    delete info;
}

/*=========================================================================
  openFilesOrDirs 
=========================================================================*/
void KFileWidget::openFilesOrDirs(const QStringList &fileNames)
{
    if (fileNames.count() > 0)
    {
        QString first = fileNames[0];
        if (QFileInfo(first).isDir())
            openSingleDir(first);
        else
            emit openFilesRequested(fileNames);
    }
}

/*=========================================================================
  slot handleOpenAction 
=========================================================================*/
void KFileWidget::handleOpenAction(void)
{
    QStringList names = getSelectedItems();
    if (names.count() == 0) return;

    QStringList fileNames;
    for (int i = 0; i < names.count(); i++)
        fileNames.append(path + "/" + names[i]);

    openFilesOrDirs(fileNames);
}

/*=========================================================================
  notifyPathDeleted
=========================================================================*/
void KFileWidget::notifyPathDeleted(const QString &pathName)
{
    int l = list->count();

    for (int i = 0; i < l; i++)
    {
        const QString testPath = path + "/" + (list->item(i))->text();
        if (pathName == testPath)
        {
            QListWidgetItem *item = list->takeItem(i);
            delete item;
            // The same item won't appear more than once, and if we continue
            //  we will run off the end of the list and crash
            break;
        }
    }
}

/*=========================================================================
  slot handleCutAction 
=========================================================================*/
void KFileWidget::handleCutAction(void)
{
    QStringList names = getSelectedItems();
    // Note that names is a list of names, not of paths
    if (names.count() == 0)
    {
        message(tr("Select files or folders to cut first."));
    }
    else
    {
        FileClipboard *fc = FileClipboard::getInstance();
        fc->setFiles(FILE_OP_CUT, path,
            names, pasteByNameOnly);
        int l = names.count();
        char ss[20];
        sprintf(ss, "%d", l);
        emit statusUpdate(tr("Cut") + " " + ss + " " +
            (l == 1 ? tr("item") : tr("items")) + " " + tr("to clipboard"));
    }
}

/*=========================================================================
  slot handleCopyAction 
=========================================================================*/
void KFileWidget::handleCopyAction(void)
{
    QStringList names = getSelectedItems();
    // Note that names is a list of names, not of paths
    if (names.count() == 0)
    {
        message(tr("Select files or folders to copy first."));
    }
    else
    {
        bool cancelled = false;
        QStringList expandedNames = expandNames(path, names, &cancelled,
            true);
        // expanded names is a list of files relative to the current value
        //  of this->path
        if (!cancelled)
        {
            if (expandedNames.count() > 0)
            {
                FileClipboard *fc = FileClipboard::getInstance();
                fc->setFiles(FILE_OP_COPY, path,
                    expandedNames, pasteByNameOnly);
                int l = expandedNames.count();
                char ss[20];
                sprintf(ss, "%d", l);
                emit statusUpdate(tr("Copied") + " " + ss + " " +
                    (l == 1 ? tr("item") : tr("items")) + " " + tr("to clipboard"));
            }
        }
    }
}

/*=========================================================================
  slot handleSettingsAction 
=========================================================================*/
void KFileWidget::handleSettingsAction(void)
{
    emit settingsRequested();
}

/*=========================================================================
  slot handleAboutAction 
=========================================================================*/
void KFileWidget::handleAboutAction(void)
{
    emit aboutRequested();
}

/*=========================================================================
  slot handleManualAction 
=========================================================================*/
void KFileWidget::handleManualAction(void)
{
    emit manualRequested();
}

/*=========================================================================
  toggetViewMode 
=========================================================================*/
void KFileWidget::toggleViewMode(void)
{
    viewMode = (ViewMode)((int)viewMode + 1);
    if ((int)viewMode >= (int)NumViewModes) viewMode = (ViewMode)0;
    setViewMode(viewMode);
}


/*=========================================================================
  toggetViewMode 
=========================================================================*/
void KFileWidget::setViewMode(ViewMode viewMode)
{
    int h = 50;
    this->viewMode = viewMode;
    switch (viewMode)
    {
    case List:
    {
        list->setViewMode(QListView::ListMode);
        list->setSpacing(0);
        QSize size(32, 32);
        list->setIconSize(size);
    }
    break;
    case GridSmallIcons:
    {
        list->setViewMode(QListView::IconMode);
        list->setSpacing(10);
        QSize size(32, 32);
        list->setIconSize(size);
        h = 60;
    }
    break;
    case GridLargeIcons:
    {
        list->setViewMode(QListView::IconMode);
        list->setSpacing(10);
        QSize size(80, 80);
        list->setIconSize(size);
        h = 128;
    }
    break;
    default: break;
    }

    int l = list->count();
    for (int i = 0; i < l; i++)
    {
        QListWidgetItem *item = list->item(i);
        QSize size(200, h);
        item->setSizeHint(size);
    }
}

/*=========================================================================
  slot handleSelectAllAction 
=========================================================================*/
void KFileWidget::handleSelectAllAction(void)
{
    int l = list->count();
    for (int i = 0; i < l; i++)
    {
        QListWidgetItem *item = list->item(i);
        item->setSelected(true);
    }
}

/*=========================================================================
  slot handleSelectNoneAction 
=========================================================================*/
void KFileWidget::handleSelectNoneAction(void)
{
    int l = list->count();
    for (int i = 0; i < l; i++)
    {
        QListWidgetItem *item = list->item(i);
        item->setSelected(false);
    }
}
