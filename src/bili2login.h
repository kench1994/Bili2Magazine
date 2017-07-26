#ifndef BILI2LOGIN_H
#define BILI2LOGIN_H

#include <QDialog>
#include <QAbstractButton>
#include <QPushButton>

#include <QDialogButtonBox>
#include "GeetTest/geettest.h"

namespace Ui {
class BiLi2Login;
}

class BiLi2Login : public QDialog
{
    Q_OBJECT

public:
    explicit BiLi2Login(QWidget *parent = 0);
    ~BiLi2Login();

public slots:



    void on_buttonBox_clicked(QAbstractButton *button);
    void slot_requestFinished(bool bSuccess,int nStateMachine, const QString &strResult);

//signals:
//    void signal_requestFinished(bool bSuccess,const QString& strResult); //http请求结束
private:
    Ui::BiLi2Login *ui;
    GeetTest *pHttpFun;
};

#endif // BILI2LOGIN_H
