#include "bili2magazine.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    BiLi2Magazine w;
    w.show();

    return a.exec();
}
