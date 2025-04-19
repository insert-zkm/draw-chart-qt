#include <QApplication>

#include "win.hpp"

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);

    Win w;
    w.show();
    Qt::WA_DeleteOnClose;
    return app.exec();
}
