#include "mainwindow.h"
#include <QApplication>

#include <string>
#include <algorithm>
#include <vector>

#include <iostream>


using namespace std;
#include "bt.h"
#include "list.h"
int main(int argc, char *argv[])
{
  bt<string> hola("yisus","god");
  hola.insert("hola","hi");
  hola.insert("bola","ball");
  hola.insert("train","entrenamiento");
  hola.find("hola");
  hola.mybegin();
  hola.next();
  hola.myend();
  hola.comparation(4,"hola");
  mylist<string> holas;
  holas.insert("holas","his");
  holas.comparation(3,"hola");
  QApplication a(argc, argv);
  MainWindow w;
  w.show();

  return a.exec();
}
