/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.4.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QComboBox *structureComboBox;
    QLabel *label;
    QLabel *label_3;
    QLineEdit *word;
    QLabel *label_4;
    QLineEdit *ratio;
    QPushButton *generateButton;
    QComboBox *dirComboBox;
    QPushButton *selectButton;
    QTableWidget *tableWidget;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(374, 346);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        structureComboBox = new QComboBox(centralWidget);
        structureComboBox->setObjectName(QStringLiteral("structureComboBox"));
        structureComboBox->setGeometry(QRect(140, 10, 101, 22));
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(20, 10, 111, 16));
        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(20, 80, 59, 14));
        word = new QLineEdit(centralWidget);
        word->setObjectName(QStringLiteral("word"));
        word->setGeometry(QRect(80, 80, 113, 22));
        label_4 = new QLabel(centralWidget);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(20, 110, 59, 14));
        ratio = new QLineEdit(centralWidget);
        ratio->setObjectName(QStringLiteral("ratio"));
        ratio->setGeometry(QRect(80, 110, 113, 22));
        generateButton = new QPushButton(centralWidget);
        generateButton->setObjectName(QStringLiteral("generateButton"));
        generateButton->setGeometry(QRect(250, 100, 101, 22));
        dirComboBox = new QComboBox(centralWidget);
        dirComboBox->setObjectName(QStringLiteral("dirComboBox"));
        dirComboBox->setGeometry(QRect(140, 40, 181, 22));
        dirComboBox->setEditable(true);
        selectButton = new QPushButton(centralWidget);
        selectButton->setObjectName(QStringLiteral("selectButton"));
        selectButton->setGeometry(QRect(19, 40, 81, 22));
        tableWidget = new QTableWidget(centralWidget);
        if (tableWidget->columnCount() < 2)
            tableWidget->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        tableWidget->setObjectName(QStringLiteral("tableWidget"));
        tableWidget->setGeometry(QRect(10, 140, 341, 141));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 374, 19));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MS", 0));
        structureComboBox->clear();
        structureComboBox->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "AVL", 0)
         << QApplication::translate("MainWindow", "Binary Tree", 0)
         << QApplication::translate("MainWindow", "Red Black Tree", 0)
         << QApplication::translate("MainWindow", "Linked List", 0)
        );
        label->setText(QApplication::translate("MainWindow", "Data Estructure:", 0));
        label_3->setText(QApplication::translate("MainWindow", "Word:", 0));
        label_4->setText(QApplication::translate("MainWindow", "Ratio:", 0));
        generateButton->setText(QApplication::translate("MainWindow", "Generate", 0));
        selectButton->setText(QApplication::translate("MainWindow", "Select file", 0));
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("MainWindow", "Word 1", 0));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("MainWindow", "Word 2", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
