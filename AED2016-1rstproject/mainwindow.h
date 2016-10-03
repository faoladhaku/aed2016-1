#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDir>
#include <QFileDialog>

#include <fstream>
#include <string>
#include <iostream>
using namespace std;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void insertAVL(QString word, QString directory, int ratio);
    void insertBT(QString word, QString directory, int ratio);
    void insertLL(QString word, QString directory, int ratio);
    void insertRB(QString word, QString directory, int ratio);

private slots:
    void browse();
    void generate();

private:
    Ui::MainWindow *ui;

    QDir currentDir;
};

#endif // MAINWINDOW_H
