#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    w.setWindowTitle("记事本cpp");
    // 将对话框宽设置为500, 高设置为300
    w.resize(800,350);


    w.show();

    return a.exec();
}
