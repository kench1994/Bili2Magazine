#include "bili2magazine.h"
#include "ui_bili2magazine.h"

BiLi2Magazine::BiLi2Magazine(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::BiLi2Magazine)
{
    ui->setupUi(this);
}

BiLi2Magazine::~BiLi2Magazine()
{
    delete ui;
}
