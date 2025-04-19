#ifndef WIN_H
#define WIN_H

#include <QMainWindow>
#include <QComboBox>
#include <QMenu>
#include <QMenuBar>
#include <QAction>

#include "filesystemwidget.hpp"
#include "chartwidget.hpp"

class Win : public QMainWindow
{
    Q_OBJECT
public:
    Win();

public slots:
    void printDisable(bool status);
protected:
    void createMenus();
    void createActions();
    void appStyle();

protected:
    FileSystemWidget* fs;
    ChartWidget* ch;

    QMenu *fileMenu;
    QAction* openAct;
    QAction* printAct;
    QAction* exitAct;
};

#endif // WIN_H
