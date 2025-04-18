#ifndef WIN_H
#define WIN_H

#include <QWidget>
#include <QComboBox>

class Win : public QWidget
{
    Q_OBJECT
public:
    Win(QWidget* parent = nullptr);
protected:
    void fillComboBoxes();

    QComboBox* dataTypeCB;
};

#endif // WIN_H
