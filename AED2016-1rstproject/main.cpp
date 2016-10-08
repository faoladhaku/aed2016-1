#include "mainwindow.h"
#include <QApplication>

#include <string>
#include <algorithm>
#include <vector>

#include <iostream>


using namespace std;
#include "bt.h"
#include "list.h"
#include "AVL.h"
#include "RBT.h"
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
  AVL<string> holita("yisus","god");
  holita.add("hola","hi");
  holita.add("train","entrenamiento");
  holita.add("bola","ball");
  holita.mybegin();
  holita.next();
  holita.myend();
  //RBT<string> holona("yisus","god");
  //holona.add("hola","hi");
  //holona.add("train","entrenamiento");
  //holona.add("bola","ball");
  //holona.mybegin();
  //holona.next();
  //holona.myend();
  QApplication a(argc, argv);
  MainWindow w;
  w.show();

  return a.exec();
}
