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
#include <QSplitter>
#include <QSplitterHandle>

Win::Win()
{
    QWidget* widget = new QWidget();
    setCentralWidget(widget);

    setMinimumSize(160, 160);
    this->resize(700, 350);

    fs = new FileSystemWidget();
    ch = new ChartWidget();

    QVBoxLayout *rootLayout = new QVBoxLayout();

    QSplitter* splitter = new QSplitter();
    rootLayout->addWidget(splitter);

    splitter->addWidget(fs);
    splitter->addWidget(ch);
    splitter->setStretchFactor(1, 20);

    widget->setLayout(rootLayout);
    statusBar()->showMessage("Выберите папку для начала работы");

    createActions();
    createMenus();
    appStyle();

    connect(fs, &FileSystemWidget::selectedFile, ch, &ChartWidget::drawChart);
    connect(ch, &ChartWidget::printStatus, this, &Win::printDisable);
}


void Win::createMenus()
{
    fileMenu = menuBar()->addMenu(tr("&File"));

    fileMenu->addAction(openAct);
    fileMenu->addAction(printAct);
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
    printAct->setDisabled(true);
    printAct->setStatusTip("Печать в PDF");
    connect(printAct, &QAction::triggered, ch, &ChartWidget::print);

    exitAct = new QAction("Выход", this);
    exitAct->setShortcuts(QKeySequence::Quit);
    exitAct->setStatusTip("ВЫйти из приложения");
    connect(exitAct, &QAction::triggered, this, &QWidget::close);
}

void Win::printDisable(bool status) {
    printAct->setDisabled(status);
}

void Win::appStyle()
{
    this->setStyleSheet(R"(
        QTableView {
            border: none;
        }
        QChart {
            border: none;
            border-radius: 0px;
        }
        QSplitter::handle{
            background-color: rgba(108, 122, 137, 20%);
        })");
}

