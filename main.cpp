#include "MainWindow.h"
#include "MainWindowPresenter.h"

#include <QApplication>

int main(int argc, char* argv[])
{
    QApplication a(argc, argv);

    MainWindow w;
    MainWindowPresenter wPresenter(&w);

    w.show();

    return a.exec();
}
