#include "win.hpp"

#include <QtCharts/QChart>
#include <QtCharts/QChartView>
#include <QtCharts/QAbstractSeries>
#include <QStringListModel>
#include <QVariant>
#include <QStatusBar>

#include <QTreeView>
#include <QLabel>
#include <QFileSystemModel>
#include <QVBoxLayout>
#include <QSizePolicy>
#include <QDebug>
#include <QFileDialog>


Win::Win()
{
    QWidget* widget = new QWidget();
    setCentralWidget(widget);

    setMinimumSize(160, 160);
    this->resize(600, 600);

    fs = new FileSystemWidget();
    QVBoxLayout *l1 = new QVBoxLayout();
    l1->addWidget(new QLabel());
    l1->addWidget(fs);

    statusBar()->showMessage("");
    widget->setLayout(l1);

    createActions();
    createMenus();
}

/*
 * void Win::fillComboBoxes() { NOTE: usage of SeparatorComboBox
    dataTypeCB->addParentItem("Time Series");
    dataTypeCB->addChildItem("Line chart", 1);
    dataTypeCB->addChildItem("Histogram chart", 2);

    dataTypeCB->addParentItem("XY Series");
    dataTypeCB->addChildItem("Line chart", 1);

    dataTypeCB->setCurrentIndex(1);
} */

void Win::createMenus()
{
    fileMenu = menuBar()->addMenu(tr("&File"));

    fileMenu->addAction(openAct);
    fileMenu->addSeparator();
    fileMenu->addAction(exitAct);
}

void Win::createActions()
{
    openAct = new QAction("Открыть...", this);
    openAct->setShortcuts(QKeySequence::Open);
    openAct->setStatusTip("Открыть существующую папку");
    connect(openAct, &QAction::triggered, fs, &FileSystemWidget::open);

    exitAct = new QAction("Выход", this);
    exitAct->setShortcuts(QKeySequence::Quit);
    exitAct->setStatusTip("ВЫйти из приложения");
    connect(exitAct, &QAction::triggered, this, &QWidget::close);
}

