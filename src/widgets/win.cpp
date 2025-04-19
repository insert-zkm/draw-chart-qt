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
    ch = new ChartWidget();

    QVBoxLayout *leftLayout = new QVBoxLayout();
    leftLayout->addWidget(fs);

    QVBoxLayout *rightLayout = new QVBoxLayout();
    rightLayout->addWidget(ch);

    QHBoxLayout *rootLayout = new QHBoxLayout();
    rootLayout->addLayout(leftLayout);
    rootLayout->addLayout(rightLayout);

    widget->setLayout(rootLayout);

    statusBar()->showMessage("Выберите папку для начала работы");

    createActions();
    createMenus();

    connect(fs, &FileSystemWidget::selectedFile, ch, &ChartWidget::drawChart);
}


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

    printAct = new QAction("Печать...", this);
    printAct->setShortcuts(QKeySequence::Print);
    printAct->setStatusTip("Открыть существующую папку");
//    connect(printAct, &QAction::triggered, fs, &FileSystemWidget::open); TODO

    exitAct = new QAction("Выход", this);
    exitAct->setShortcuts(QKeySequence::Quit);
    exitAct->setStatusTip("ВЫйти из приложения");
    connect(exitAct, &QAction::triggered, this, &QWidget::close);
}

