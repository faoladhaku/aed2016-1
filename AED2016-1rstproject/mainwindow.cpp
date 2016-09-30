#include "mainwindow.h"
#include "ui_mainwindow.h"

//#include

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tableWidget->horizontalHeader()->setStretchLastSection(true);

    QObject::connect(ui->selectButton,SIGNAL(clicked(bool)),this,SLOT(browse()));

    //QString fileName = QFileDialog::getOpenFileName(this,tr("Open Image"), "/home", tr("Text files (*.txt)"));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::browse()
{
    QString directory = QFileDialog::getExistingDirectory(this,
                               tr("Find Files"), QDir::currentPath());

    if (!directory.isEmpty()) {
        if (ui->dirComboBox->findText(directory) == -1)
            ui->dirComboBox->addItem(directory);
        ui->dirComboBox->setCurrentIndex(ui->dirComboBox->findText(directory));
    }
}
