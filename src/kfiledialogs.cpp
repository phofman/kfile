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

#include "kfiledialogs.h"

/*=========================================================================
  message
=========================================================================*/
void KFileDialogs::message(const QString &message, QWidget *parent)
{
    QMessageBox msgBox(parent);
    msgBox.setText(message);
    msgBox.exec();
}

/*=========================================================================
  error 
=========================================================================*/
void KFileDialogs::error(const QString &message, QWidget *parent)
{
    QMessageBox msgBox(parent);
    msgBox.setText(message);
    msgBox.setIcon(QMessageBox::Critical);
    msgBox.setWindowTitle("Error");
    msgBox.exec();
}


