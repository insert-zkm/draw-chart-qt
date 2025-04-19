#include "filesystemwidget.hpp"
#include "includes/filetablemodel.hpp"
#include "qpdfwriter.h"

#include <QLabel>

#include <QVBoxLayout>
#include <QSizePolicy>
#include <QDebug>
#include <QFileDialog>
#include <QHeaderView>
#include <QAbstractItemView>
#include <QHeaderView>
#include <QMessageBox>

QStringList filesFilter = {"*.sqlite", "*.json"};

FileSystemWidget::FileSystemWidget()
{
    QVBoxLayout *l1 = new QVBoxLayout(this);
    l1->addWidget(new QLabel("Выбор файла с данными"));

    fileModel = new FileTableModel(this);

    fileModel->newFiles(QDir("../draw-chart-qt/test/data/"));

    tv = new QTableView();
    tv->setModel(fileModel);
    tv->verticalHeader()->hide();
    QHeaderView *headerView = tv->horizontalHeader();
    headerView->setSectionResizeMode(0, QHeaderView::Stretch);
    headerView->setSectionResizeMode(1, QHeaderView::Interactive);
    tv->setSelectionBehavior(QAbstractItemView::SelectRows);
    tv->setSelectionMode(QAbstractItemView::SingleSelection);

    l1->addWidget(tv);

    connect(tv, &QTableView::activated, this,  &FileSystemWidget::modelItemActivated);
}

void FileSystemWidget::open()
{
    QString dirPath = QFileDialog::getExistingDirectory(
        this,
        "Открыть папку",
        QDir::homePath(),
        QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);

    if(dirPath.isEmpty()) {
        return;
    }
    QDir dir(dirPath);
    dir.setNameFilters(filesFilter);

    if(dir.isEmpty()) {
        QMessageBox::information(this,
                                 "Выбрана пустая папка",
                                 "Вернуться?");
    }

    fileModel->newFiles(dir);
}

void FileSystemWidget::modelItemActivated(const QModelIndex& current) const {
    emit selectedFile(fileModel->fileInfo(current.row()));
}
