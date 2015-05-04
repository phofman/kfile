#include <unistd.h> 
#include <QApplication>
#include <QPushButton>
#include <QWidget>
#include <QListWidget>
#include <QDir>
#include <QStringList>
#include <QMessageBox>
#include <QVBoxLayout>
#include <QAction>
#include <QToolBar>
#include <QAbstractItemView>
#include <QInputDialog>
#include <QProgressDialog>
#include <QToolButton>
#include <QMenu>

#include "kfiledialogs.h"

/*=========================================================================
  message
=========================================================================*/
void KFileDialogs::message (const QString &message, QWidget *parent)
 {
 QMessageBox msgBox (parent);
 msgBox.setText(message);
 msgBox.exec();
 }

/*=========================================================================
  error 
=========================================================================*/
void KFileDialogs::error (const QString &message, QWidget *parent)
 {
 QMessageBox msgBox (parent);
 msgBox.setText(message);
 msgBox.setIcon(QMessageBox::Critical);
 msgBox.setWindowTitle("Error");
 msgBox.exec();
 }


