#include "mainwindow.h"

#include <QApplication>
MainWindow *wnd;
int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  MainWindow w;
  wnd = &w;
  w.show();
  return a.exec();
}
