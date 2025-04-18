#include "filesystemwidget.hpp"
#include "includes/filetablemodel.hpp"

#include <QLabel>

#include <QVBoxLayout>
#include <QSizePolicy>
#include <QDebug>
#include <QFileDialog>
#include <QHeaderView>
#include <QAbstractItemView>
#include <QHeaderView>


QStringList filesFilter = {"*.sqlite", "*.json"};

FileSystemWidget::FileSystemWidget()
{
    QVBoxLayout *l1 = new QVBoxLayout(this);
    l1->addWidget(new QLabel("Выбор файла с данными"));

    fileModel = new FileTableModel(this);
    tv = new QTableView();
    tv->setModel(fileModel);
    tv->verticalHeader()->hide();
    QHeaderView *headerView = tv->horizontalHeader();
    headerView->setSectionResizeMode(0, QHeaderView::Stretch);
    headerView->setSectionResizeMode(1, QHeaderView::Interactive);
    tv->setSelectionBehavior(QAbstractItemView::SelectRows);

    l1->addWidget(tv);
}

void FileSystemWidget::open()
{
    QString dirPath = QFileDialog::getExistingDirectory(
        this,
        "Открыть папку",
        QDir::homePath(),
        QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);

    QDir dir(dirPath);
    dir.setNameFilters(filesFilter);
    if(dir.isEmpty()) {
        // message box
    }
    fileModel->newFiles(dir);

    // set connections
}
