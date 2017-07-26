#include "bili2login.h"
#include "ui_bili2login.h"

extern int StateMachine;
BiLi2Login::BiLi2Login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::BiLi2Login)
{
    ui->setupUi(this);

}

BiLi2Login::~BiLi2Login()
{
    delete ui;
}



void BiLi2Login::on_buttonBox_clicked(QAbstractButton *button)
{
    pHttpFun = new GeetTest();
    connect(pHttpFun,SIGNAL(signal_requestFinished(bool,int,const QString&)), //http请求结束信号
            this,SLOT(slot_requestFinished(bool,int,const QString&)));
    //发送第一个包
    pHttpFun->CaptchaGc();

//    else if(button == ui->buttonBox->button(QDialogButtonBox::Cancel))

}

void BiLi2Login::slot_requestFinished(bool bSuccess, int nStateMachine, const QString &strResult){
//    qDebug()<<nStateMachine;
//    qDebug()<<strResult;


    if(bSuccess){
        pHttpFun = new GeetTest();
        connect(pHttpFun,SIGNAL(signal_requestFinished(bool,int,const QString&)), //http请求结束信号
                this,SLOT(slot_requestFinished(bool,int,const QString&)));


        if(nStateMachine == 0x11){
            StateMachine = 0x02;
//            qDebug()<<"gt:"<<pHttpFun->str_gt;
//            qDebug()<<"challenge:"<<pHttpFun->str_challenge;
//            qDebug()<<"正在发送第2个包";

            pHttpFun->SendGt();
        }else if(nStateMachine==0x12){
            StateMachine = 0x03;
            pHttpFun->GetPic();
        }else if(nStateMachine == 0x13){
            StateMachine = 0x00;

        }

    }
//    else
//    {
//        ui->resultEdit->setPlainText(tr("请求失败！"));
//    }

}
