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

protected:
    void createMenus();
    void createActions();

protected:
    FileSystemWidget* fs;
    ChartWidget* ch;

    QMenu *fileMenu;
    QAction* openAct;
    QAction* printAct;
    QAction* exitAct;
};

#endif // WIN_H
