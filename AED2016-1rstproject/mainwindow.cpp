#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "list.h"
#include "bt.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tableWidget->horizontalHeader()->setStretchLastSection(true);

    QObject::connect(ui->selectButton,SIGNAL(clicked(bool)),this,SLOT(browse()));
    QObject::connect(ui->generateButton,SIGNAL(clicked(bool)),this,SLOT(generate()));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::insertAVL(QString word, QString directory, int ratio)
{

}

void MainWindow::insertLL(QString word, QString directory, int ratio)
{
    mylist<string> ms;

    QFile file(directory);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;
    while (!file.atEnd()) {
        QByteArray line = file.readLine();
        string l = line.data();
        string w1, w2;
        bool flag = true;
        for(int i=0;i<l.length()-1;i++){
            if( l[i] == ';' ){
                flag = false;
                i++;
            }
            if(flag)
               w1 +=l[i];
            if(!flag)
               w2 +=l[i];
        }
        cout << w1 << " " << w2 << endl;
        ms.insert(w1,w2);
    }

    ms.current = ms.begin();
    nodo<string> *tmp = ms.head;

    while(tmp){

        if(tmp == ms.tail)
            break;

        if( ms.levenshtein(word.toStdString(),tmp->dato[0]) <= ratio) {

            QString w1 = QString::fromStdString(tmp->dato[0]);
            QString w2 = QString::fromStdString(tmp->dato[1]);
            QTableWidgetItem *word_1 = new QTableWidgetItem();
            word_1->setText(w1);
            QTableWidgetItem *word_2 = new QTableWidgetItem();
            word_2->setText(w2);

            int row = ui->tableWidget->rowCount();
            ui->tableWidget->insertRow(row);
            ui->tableWidget->setItem(row, 0, word_1);
            ui->tableWidget->setItem(row, 1, word_2);
        }

        tmp = tmp->siguiente;
    }
}

void MainWindow::insertRB(QString word, QString directory, int ratio)
{

}

void MainWindow::insertBT(QString word, QString directory, int ratio)
{
    bt<string> ms("mary","ms");

    QFile file(directory);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;
    while (!file.atEnd()) {
        QByteArray line = file.readLine();
        string l = line.data();
        string w1, w2;
        bool flag = true;
        for(int i=0;i<l.length()-1;i++){
            if( l[i] == ';' ){
                flag = false;
                i++;
            }
            if(flag)
               w1 +=l[i];
            if(!flag)
               w2 +=l[i];
        }
        cout << w1 << " " << w2 << endl;
        ms.insert(w1,w2);
    }

    //cout << ms.root->dato[0] ;
    ms.mybegin();

    while(ms.current){

        cout << ms.levenshtein(word.toStdString(),ms.current->dato[0]) << endl;
        if( ms.levenshtein(word.toStdString(),ms.current->dato[0]) <= ratio) {
            QString w1 = QString::fromStdString(ms.current->dato[0]);
            QString w2 = QString::fromStdString(ms.current->dato[1]);
            QTableWidgetItem *word_1 = new QTableWidgetItem();
            word_1->setText(w1);
            QTableWidgetItem *word_2 = new QTableWidgetItem();
            word_2->setText(w2);

            int row = ui->tableWidget->rowCount();
            ui->tableWidget->insertRow(row);
            ui->tableWidget->setItem(row, 0, word_1);
            ui->tableWidget->setItem(row, 1, word_2);
        }

        ms.current = ms.next();
    }
}

void MainWindow::browse()
{
    QString directory = QFileDialog::getOpenFileName(this,tr("Open File"), "/home");
    //QString directory = QFileDialog::getExistingDirectory(this,tr("Find Files"), QDir::currentPath());

    if (!directory.isEmpty()) {
        if (ui->dirComboBox->findText(directory) == -1)
            ui->dirComboBox->addItem(directory);
        ui->dirComboBox->setCurrentIndex(ui->dirComboBox->findText(directory));
    }
}

void MainWindow::generate()
{
    ui->tableWidget->setRowCount(0);
    QString word = ui->word->text();
    QString ratio = ui->ratio->text();
    int structure = ui->structureComboBox->currentIndex();
    QString directory = ui->dirComboBox->currentText();

    // get the chosen structure and then add all the words
    switch(structure){
        case 0: {insertAVL(word, directory, ratio.toInt()); break;}
        case 1: {insertBT(word, directory, ratio.toInt()); break;}
        case 2: {insertRB(word, directory, ratio.toInt()); break;}
        case 3: {insertLL(word, directory, ratio.toInt()); break;}
    }

    // ez game
}
