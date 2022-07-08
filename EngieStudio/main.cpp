#include "MainWindow.h"
#include <QApplication>
#include <QSet>
#include <QtDebug>
#include <DealWithXML.h>
#include <set>
using namespace std;

int main(int argc, char *argv[])
{
    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication a(argc, argv);

    MainWindow w;
    w.show();
    return a.exec();
}
