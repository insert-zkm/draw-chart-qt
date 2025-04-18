#include "filesystemwidget.hpp"
#include "includes/filetablemodel.hpp"

#include <QLabel>

#include <QVBoxLayout>
#include <QSizePolicy>
#include <QDebug>
#include <QFileDialog>


QStringList files = {"*.sqlite", "*.json"};

FileSystemWidget::FileSystemWidget()
{
    QVBoxLayout *l1 = new QVBoxLayout(this);
    l1->addWidget(new QLabel("Выбор файла с данными"));

    fileModel = new FileTableModel(this);
    fileModel->newFiles(QDir::current());
    tv = new QTableView();
    tv->setModel(fileModel);
    qDebug() << tv->rootIndex();

    l1->addWidget(tv);
}

void FileSystemWidget::open()
{
    QString dir = QFileDialog::getExistingDirectory(
        this,
        "Открыть папку",
        QDir::homePath(),
        QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);


//    tv->setRootIndex(dir);
}
