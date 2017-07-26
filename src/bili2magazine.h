#ifndef BILI2MAGAZINE_H
#define BILI2MAGAZINE_H

#include <QMainWindow>

namespace Ui {
class BiLi2Magazine;
}

class BiLi2Magazine : public QMainWindow
{
    Q_OBJECT

public:
    explicit BiLi2Magazine(QWidget *parent = 0);
    ~BiLi2Magazine();

private:
    Ui::BiLi2Magazine *ui;
};

#endif // BILI2MAGAZINE_H
