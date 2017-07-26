//#include "bili2magazine.h"
#include "bili2login.h"
#include <QApplication>

int StateMachine = 0x00;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    BiLi2Login w;
    w.show();


    return a.exec();
}
