#include "fileclipboard.h"

FileClipboard *FileClipboard::instance = 0;

/*=========================================================================
  getInstance
=========================================================================*/
FileClipboard *FileClipboard::getInstance(void)
{
    if (!instance)
        instance = new FileClipboard();

    return instance;
}

/*=========================================================================
  clear 
=========================================================================*/
void FileClipboard::clear(void)
{
    root = "";
    names.clear();
    op = FILE_OP_NONE;
    pasteByNameOnly = false;
}

/*=========================================================================
  setFiles 
=========================================================================*/
void FileClipboard::setFiles(FileClipboardOp op, const QString &root, const QStringList &names, bool pasteByNameOnly)
{
    clear();
    this->op = op;
    this->root = root;
    this->names = names;
    this->pasteByNameOnly = pasteByNameOnly;
}

