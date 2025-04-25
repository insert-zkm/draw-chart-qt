#ifndef FILESYSTEMWIDGET_H
#define FILESYSTEMWIDGET_H
#include <QWidget>
#include <QPainter>
#include <QTableView>
#include <QFileSystemModel>

#include "includes/filetablemodel.hpp"

class FileSystemWidget : public QWidget
{
    Q_OBJECT
public:
    FileSystemWidget();
signals:
    void selectedFile(const QFileInfo& fi) const;

public slots:
    void open();
    void modelItemActivated(const QModelIndex& current) const;

protected:
    QFileSystemModel* fileModel;
    QTableView* tv;
};

#endif // FILESYSTEMWIDGET_H
