#include "mainwindow.h"
#include <QApplication>
#include "bt.h"
#include "list"
int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  MainWindow w;
  w.show();

  return a.exec();
}
