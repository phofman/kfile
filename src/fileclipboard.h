#pragma once
#include <QStringList>

typedef enum
  {
  FILE_OP_NONE = 0,
  FILE_OP_COPY = 1,
  FILE_OP_CUT
  } FileClipboardOp;

class FileClipboard
  {
  public:

  static FileClipboard *getInstance (void);
  void clear (void);
  void setFiles (FileClipboardOp op, const QString &root, 
    const QStringList &names, bool pasteByNameOnly);
  const QStringList &getNames() const { return names; }
  const QString &getRoot() const { return root; }
  FileClipboardOp getOp() const { return op; }
  bool getPasteByNameOnly() const { return pasteByNameOnly; }


  protected:

  static FileClipboard *instance;
  QStringList names;
  QString root;
  FileClipboardOp op;
  bool pasteByNameOnly;
  };
 

