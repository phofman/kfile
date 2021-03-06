#include <QApplication>
#include <QPushButton>
#include <QWidget>
#include <QListWidget>
#include <QVBoxLayout>
#include <QImageReader>
#include "kfilebrowser.h" 
#include "mainwindow.h" 
#include "kfilestyle.h" 
#include "kfiledialogs.h" 

/*=========================================================================
  main 
=========================================================================*/
int main(int argc, char *argv[])
  {
  QCoreApplication::addLibraryPath("app/native/lib");
  QApplication app(argc, argv);

  app.setStyle (new KFileStyle);
  app.setDoubleClickInterval (800);
  app.setStartDragDistance (16);

  KFileSettings::getGlobalInstance()->load();
  MainWindow window (&app);

  window.showMaximized();

  app.exec();
  return 0;
  }
