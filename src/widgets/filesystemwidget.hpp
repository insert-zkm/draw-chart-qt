#ifndef FILESYSTEMWIDGET_H
#define FILESYSTEMWIDGET_H
#include <QWidget>
#include <QPainter>
#include <QTableView>

#include "includes/filetablemodel.hpp"

class FileSystemWidget : public QWidget
{
    Q_OBJECT
public:
    FileSystemWidget();

public slots:
    void open();

protected:
    FileTableModel* fileModel;
    QTableView* tv;
};

#endif // FILESYSTEMWIDGET_H
